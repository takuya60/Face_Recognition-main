#include "face_opencv.h"
#include <stdio.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
//#include <experimental/filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>

using namespace cv;
using namespace std;

//namespace fs=std::experimental::filesystem;

face_processor::face_processor(){}
face_processor::~face_processor(){}

bool face_processor::initialize(const std::string& cascadePath)
{
    //加载人脸检测模型
    if(!faceDetector.load(cascadePath))
    {
        cerr<<"[ERROR]failed to load cascade"<<cascadePath<<endl;
        return false;
    }
    //初始化LBPH识别器/人脸识别模型
    faceRecognizer = cv::face::createLBPHFaceRecognizer();

    loadDatabase();
    // --- 一次性加载所有姓名到 m_nameMap ---
    std::cout << "[INFO] Loading names from face_labels.txt..." << std::endl;
    // (确保这个路径是你在 i.MX6U 上的 *绝对* 路径)
    std::ifstream fin("/mnt/tf/face_labels.txt"); 
    
    if (fin)
    {
        int id;
        std::string name;
        // 循环读取文件所有行
        while (fin >> id >> name)
        {
            m_nameMap[id] = name; // 存入 map
            std::cout << "  -> Loaded ID " << id << " = " << name << std::endl;
        }
        fin.close();
    } else {
        std::cerr << "[WARN] Could not open face_labels.txt. Names will not be shown." << std::endl;
    }
    // --- 加载姓名结束 --

    cout<<"[INFO] Face processor initialized"<<endl;
    return true;
}

RecognitionResult face_processor::processFrame(const cv::Mat& frame)
{
    RecognitionResult result;
    result.is_foundface=false;
    result.is_known=false;
    result.name="Unknown";
    result.person_id=-1;
    result.confidence = 0.0;

    if (frame.empty())
        return result;

    Mat gray;
    //cvtcolor 色彩转换函数（convertcolor）
    //COLOR_BayerBG2GRAY 指定从BGR转化成灰度
    //人脸检测和 LBPH 识别算法通常在灰度图上运行
    cvtColor(frame,gray,COLOR_BGR2GRAY);
    //增强灰度图的对比度
    equalizeHist(gray,gray);

    //1.2是缩放因子，越靠近1，精细+慢
    //5 最小邻居数，越大越严格，不会把其它东西当成人脸，这里5属于较大
    vector<Rect>faces;
    faceDetector.detectMultiScale(gray,faces,1.2,5,0,Size(80,80));

    if (faces.empty())
        return result;

    result.is_foundface=true;
    result.face_position=faces[0];
    //从gray图像中把人脸的部分抠出来
    Mat faceROI=gray(faces[0]);

    if(faceRecognizer)
    {
        int label=-1;
        double confidence =0.0;
        faceRecognizer->predict(faceROI,label,confidence);
        result.confidence = confidence;
        if( confidence<80.0)
        {
            result.is_known=true;
            result.person_id=label;
            if (m_nameMap.count(label)) {
                // .count() 检查 key 是否存在
                result.name = m_nameMap[label]; // 从 map 中瞬间找到名字
            } else {
                result.name = "ID_Not_In_Map"; // (找到了但 map 中没名字)
            }
        }

    }
    return result;
}

bool face_processor::isIdRegistered(int employeeId) const
{
    return (m_nameMap.count(employeeId)>0);
}

/**
 * @brief 注册新的人脸
 */
bool face_processor::enrollNewFace(const cv::Mat& faceImage, int employeeId, const std::string& employeeName)
{
    if (faceImage.empty())
        return false;

    // --- 1. (不变) 保存图像到 face_db/ ---
    string saveDir = "/mnt/tf/face_db/";
    struct stat st = {0};
    if (stat(saveDir.c_str(), &st) == -1) {
        mkdir(saveDir.c_str(), 0755);
    }
    string filename = saveDir + "person_" + to_string(employeeId) + ".png";
    imwrite(filename, faceImage);

    // --- 2. (不变) 重新加载所有图像并训练 ---
    vector<Mat> images;
    vector<int> labels;
    DIR* dir = opendir(saveDir.c_str());
    if (!dir) { /* ... 错误处理 ... */ return false; }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        // ... (和你的旧代码一样，遍历所有 .png)
        // ... (解析 id, images.push_back(img), labels.push_back(id))
        // (我将简化这里的 POSIX C 代码，只保留关键部分)
        string fname = entry->d_name;
        if (fname == "." || fname == "..") continue;
        string fullPath = saveDir + fname;
        struct stat pathStat;
        if (stat(fullPath.c_str(), &pathStat) == 0 && S_ISREG(pathStat.st_mode)) {
             Mat img = imread(fullPath, IMREAD_GRAYSCALE);
             if (!img.empty() && fname.find("person_") == 0) {
                 string id_str = fname.substr(7, fname.find(".png") - 7);
                 int id = stoi(id_str);
                 images.push_back(img);
                 labels.push_back(id);
             }
        }
    }
    closedir(dir);

    if (images.empty()) { /* ... 错误处理 ... */ return false; }

    faceRecognizer->train(images, labels);
    faceRecognizer->save("/mnt/tf/face_model.xml"); // (使用绝对路径)

    cout << "[INFO] face_model.xml 已更新。" << endl;

    // --- 3. (新!) 更新 face_labels.txt ---
    // (这个逻辑从 enroll_tool 移到了引擎内部)
    std::ofstream fout("/mnt/tf/face_labels.txt", std::ios_base::app); 
    if (!fout) {
        cerr << "[ERROR] 无法打开 face_labels.txt 进行写入！" << endl;
        return false; // (模型更新了，但标签没更新，这不好)
    }
    fout << employeeId << " " << employeeName << endl;
    fout.close();
    cout << "[INFO] face_labels.txt 已更新。" << endl;

    // --- 4. (新!) 立即更新内存中的 map ---
    // (这是解决“重启才能显示”问题的关键)
    m_nameMap[employeeId] = employeeName;
    cout << "[INFO] 内存中的 m_nameMap 已更新。" << endl;

    cout << "[INFO] Added new face ID=" << employeeId << " and updated database." << endl;
    return true;
}
void face_processor::loadDatabase()
{
    struct stat st;
    if (stat("/mnt/tf/face_model.xml", &st) == 0) {
        faceRecognizer->load("/mnt/tf/face_model.xml");
    } else {
        cout << "[INFO] No model found." << endl;
    }
}