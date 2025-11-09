#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
/**
 * @brief 这是一个独立的工具，用于从摄像头抓拍一张照片并保存。
 * * 用法: ./capture_tool <output_filename.png>
 * * 示例: ./capture_tool zhangsan.png
 */
int main(int argc, char* argv[]) {

    

    if (argc != 2) {
        std::cerr << "用法: " << argv[0] << " <output_filename.png>" << std::endl;
        return -1;
    }
    const string SAVE_DIR = "/mnt/tf/captures/";
    std::string outputFilename = argv[1];
    string fullOutputPath = SAVE_DIR + outputFilename;

    cv::VideoCapture cap(0); // 打开默认摄像头
    if (!cap.isOpened()) {
        std::cerr << "错误: 无法打开摄像头！" << std::endl;
        return -1;
    }

    std::cout << "正在打开摄像头... 请在 3 秒后保持姿势..." << std::endl;
    
    // 给用户 3 秒钟准备时间
    // 我们用循环读取几帧来“预热”摄像头
    for (int i = 0; i < 90; ++i) {
        cv::Mat tempFrame;
        cap >> tempFrame;
        if (i == 30) std::cout << "2..." << std::endl;
        if (i == 60) std::cout << "1..." << std::endl;
        // 简单的延时
        cv::waitKey(33); 
    }

    std::cout << "拍照！" << std::endl;
    
    cv::Mat frame;
    cap >> frame; // 抓取最终帧

    if (frame.empty()) {
        std::cerr << "错误: 无法抓取到帧！" << std::endl;
        return -1;
    }

    // 保存文件
    if (cv::imwrite(fullOutputPath, frame)) 
    {
        std::cout << "[SUCCESS] 成功保存快照到: " << fullOutputPath << std::endl;
    } 
    else 
    {
        std::cerr << "[FAILED] 无法保存文件！" << std::endl;
        return -1;
    }

    return 0;
}