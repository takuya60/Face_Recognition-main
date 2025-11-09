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

    cout<<"[INFO] Face processor initialized"<<endl;
    return true;
}

RecognitionResult face_processor::processFrame(const cv::Mat& frame)
{
    RecognitionResult result;
    result.is_foundface=false;
    result.is_kown=false;
    result.name="Unkown";
    result.person_id=-1;

    if (frame.empty())
        return result;

    Mat gray;
    //cvtcolor 色彩转换函数（convertcolor）
    //COLOR_BayerBG2GRAY 指定从BGR转化成灰度
    //人脸检测和 LBPH 识别算法通常在灰度图上运行
    cvtColor(frame,gray,COLOR_BayerBG2GRAY);
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
        double condfidence =0.0;
        faceRecognizer->predict(faceROI,label,condfidence);
        if( condfidence<80.0)
        {
            result.is_kown=true;
            result.person_id=label;
            std::ifstream fin("face_labelss.txt");
            if(fin)
            {
                int id;
                string name;
                //读取fin里面的id和name
                while (fin>>id>>name)
                {
                    if(id == label)
                    {
                        result.name=name;
                        break;
                    }

                }
                
            }
        }

    }
    return result;
}

/**
 * @brief 注册新的人脸
 */
bool face_processor::enrollNewFace(const cv::Mat& faceImage, int employeeId)
{
    if (faceImage.empty())
        return false;

    string saveDir = "face_db/";
    // 使用 POSIX mkdir 创建目录
    struct stat st = {0};
    if (stat(saveDir.c_str(), &st) == -1) {
        mkdir(saveDir.c_str(), 0755);
    }

    string filename = saveDir + "person_" + to_string(employeeId) + ".png";
    imwrite(filename, faceImage);

    vector<Mat> images;
    vector<int> labels;

    DIR* dir = opendir(saveDir.c_str());
    if (!dir) {
        cerr << "[ERROR] Cannot open directory: " << saveDir << endl;
        return false;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string fname = entry->d_name;
        if (fname == "." || fname == "..") continue;

        string fullPath = saveDir + fname;

        struct stat pathStat;
        if (stat(fullPath.c_str(), &pathStat) == 0 && S_ISREG(pathStat.st_mode)) {
            Mat img = imread(fullPath, IMREAD_GRAYSCALE);
            if (!img.empty()) {
                if (fname.find("person_") == 0 && fname.find(".png") != string::npos) {
                    string id_str = fname.substr(7, fname.find(".png") - 7);
                    int id = stoi(id_str);
                    images.push_back(img);
                    labels.push_back(id);
                }
            }
        }
    }
    closedir(dir);

    if (images.empty()) {
        cerr << "[WARN] No face images found in database folder!" << endl;
        return false;
    }

    faceRecognizer->train(images, labels);
    faceRecognizer->save("face_model.xml");

    cout << "[INFO] Added new face ID=" << employeeId << " and updated database." << endl;
    return true;
}

void face_processor::loadDatabase()
{
    struct stat st;
    if (stat("face_model.xml", &st) == 0) {
        faceRecognizer->load("face_model.xml");
    } else {
        cout << "[INFO] No model found." << endl;
    }
}