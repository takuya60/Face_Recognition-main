#pragma
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>

struct RecognitionResult
{
    bool is_foundface;
    bool is_kown;
    int person_id;
    std::string name;
    cv:: Rect face_position;
};

class face_processor
{

public:
    face_processor(/* args */);
    ~face_processor();

    bool initialize(const std::string& cascadePath);
    /**
     * @brief 初始化引擎，加载所有模型
     * @param cascadePath LBP/Haar 模型文件的路径
     * @return true 如果加载成功
    */

    RecognitionResult processFrame(const cv::Mat& frame);
    /**
     * @brief 核心功能：处理来自摄像头的每一帧图像
     * @param frame 从摄像头传入的原始 cv::Mat 图像
     * @return RecognitionResult 包含所有识别结果的结构体
     */

    bool enrollNewFace(const cv::Mat& faceImage, int employeeId);
    /**
     * @brief (你的功能) 录入新员工
     * @param faceImage 截取到的人脸图像
     * @param employeeId 要分配的 ID
     * @return true 如果录入成功
     */

private:
    //找到人脸，返回方框
    cv::CascadeClassifier faceDetector; // LBP 人脸检测器
    //识别人脸，返回id
    cv::Ptr <cv::face::LBPHFaceRecognizer> faceRecognizer; // LBPH 人脸识别器
    void loadDatabase();
};
