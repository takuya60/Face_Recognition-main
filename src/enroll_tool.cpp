#include <opencv2/opencv.hpp> // 用于图像处理和检测
#include "face_opencv.h" // 包含你写的类
#include <iostream>
#include <string>
#include <vector>
#include <fstream> // 用于写入 face_labels.txt

using namespace std;
using namespace cv;

/**
 * @brief 这是一个独立的工具，用于录入新员工
 * * 用法: ./enroll_tool <id> <name> <image_path>
 * * <cascade_path>: haarcascade 模型的路径 (用于检测人脸)
 * <id>:           要分配的员工 ID (例如: 7)
 * <name>:         员工姓名 (例如: ZhangSan)
 * <image_path>:   包含该员工人脸的照片的路径
 */
int main(int argc, char* argv[]) {

    
    
    
    // --- 1. 解析命令行参数 ---
    if (argc != 4) {
        cerr << "错误：参数数量不正确。" << endl;
        cerr << "用法: " << argv[0] << " <id> <name> <image_path>" << endl;
        cerr << "示例: " << argv[0] << "  7 ZhangSan /mnt/tf/zhangsan.png" << endl;
        return -1;
    }

    string cascadePath = argv[1];
    int employeeId = -1;
    try {
        employeeId = stoi(argv[1]); // 将字符串 ID 转换为整数
    } catch (const std::exception& e) {
        cerr << "错误: ID " << argv[1] << " 不是一个有效的数字。" << endl;
        return -1;
    }

    const string CAPTURE_DIR = "/mnt/tf/captures/";
    string employeeName = argv[2];
    string imagePath = argv[3];
    string fullImagePath = CAPTURE_DIR + imagePath;

    cout << "[INFO] 准备录入 ID: " << employeeId << ", 姓名: " << employeeName << ", 图像: " << imagePath << endl;

    // --- 2. 加载并检测照片中的人脸 ---
    // 这个工具 *自己* 需要一个人脸检测器，来从照片中把人脸抠出来
    
    CascadeClassifier faceDetector;
    if (!faceDetector.load(cascadePath)) {
        cerr << "错误: 无法加载人脸检测器 " << cascadePath << endl;
        return -1;
    }

    Mat fullImage = imread(fullImagePath);
    if (fullImage.empty()) {
        cerr << "错误: 无法加载图像 " << imagePath << endl;
        return -1;
    }

    Mat gray;
    cvtColor(fullImage, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, gray);

    vector<Rect> faces;
    faceDetector.detectMultiScale(gray, faces, 1.2, 5, 0, Size(80, 80));

    if (faces.empty()) {
        cerr << "错误: 在 " << imagePath << " 中未检测到任何人脸！" << endl;
        return -1;
    }

    // 假设照片中最大的人脸就是我们要录入的人
    Rect biggestFace = faces[0];
    if (faces.size() > 1) {
        cout << "[WARN] 照片中检测到 " << faces.size() << " 张人脸。将只使用最大的那一张。" << endl;
        for (const auto& rect : faces) {
            if (rect.area() > biggestFace.area()) {
                biggestFace = rect;
            }
        }
    }

    // 裁剪出人脸 (灰度图)
    Mat faceROI = gray(biggestFace);
    cout << "[INFO] 已从照片中成功检测并裁剪出人脸。" << endl;

    // --- 3. 初始化处理器并调用 enroll ---
    
    face_processor processor;
    // 我们必须调用 initialize，因为它会创建 faceRecognizer 对象
    if (!processor.initialize(cascadePath)) {
        cerr << "错误: face_processor 初始化失败！" << endl;
        return -1;
    }

    // 调用你的 enrollNewFace 函数，它会更新 face_model.xml
    if (!processor.enrollNewFace(faceROI, employeeId)) {
        cerr << "错误: 录入失败！(enrollNewFace 返回 false)" << endl;
        return -1;
    }

    cout << "[INFO] `face_model.xml` 已成功更新。" << endl;

    // --- 4. (关键!) 更新 face_labels.txt ---
    // enrollNewFace 只更新了模型，我们还必须更新名字映射
    
    // std::ios_base::app 的意思是“追加”(append)
    // 这会在文件末尾添加新行，而不会覆盖旧内容
    ofstream fout("face_labels.txt", std::ios_base::app); 
    if (!fout) {
        cerr << "错误: 无法打开 face_labels.txt 进行写入！" << endl;
        // 注意：模型已经更新了，但标签文件更新失败了
        return -1;
    }

    fout << employeeId << " " << employeeName << endl;
    fout.close();

    cout << "[INFO] `face_labels.txt` 已成功更新。" << endl;
    cout << "========================================" << endl;
    cout << "[SUCCESS] 成功录入新员工！" << endl;
    cout << "========================================" << endl;

    return 0;
}