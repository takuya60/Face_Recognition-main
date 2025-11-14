#include "FaceWorker.h"
#include <QDebug>       // (用于在 Qt 终端打印)
#include <sstream>      // (用于格式化置信度)
#include <iomanip>      // (用于 std::setprecision)
#include <QThread>      // (用于 msleep)
#include <string> // <-- (重要) 确保你包含了 <string>

// (注册元类型)
FaceWorker::FaceWorker(QObject *parent) 
    : QObject(parent), m_isRunning(false),m_snapshotRequested(false),m_lastRecognizedId(-1)
{
    // 注册 RecognitionResult，使其可以在信号/槽中传递
    qRegisterMetaType<RecognitionResult>("RecognitionResult");
}

FaceWorker::~FaceWorker()
{
    stopProcessing();
}

/**
 * @brief (槽) 启动循环。
 * (这个函数将在 *工作线程* 中运行)
 */
void FaceWorker::startProcessing(int deviceId)
{
    // 1. (硬编码) 初始化你的引擎
    // (我们假定你已使用 "std::map 优化" 修改了 initialize() )
    const std::string cascadePath = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
    if (!m_processor.initialize(cascadePath)) 
    {
        emit statusChanged("错误: 后端引擎初始化失败！");
        return;
    }
    
    // 2. 打开摄像头 (使用我们确定的 ID, 比如 1, 对应 /dev/video1)
    std::string videoPath = "/dev/video" + std::to_string(deviceId);
    m_cap.open(videoPath, cv::CAP_V4L2); 
    if (!m_cap.isOpened()) {
        emit statusChanged(QString("错误: 无法打开摄像头 ID: %1").arg(deviceId));
        return;
    }

    emit statusChanged("摄像头已打开，开始处理...");
    m_isRunning = true;

    // --- 3. 核心循环 (在工作线程中运行，不会冻结 UI) ---
    while (m_isRunning) 
    {
        cv::Mat frame_1080p;
        if (!m_cap.read(frame_1080p)) { // (使用 .read() 更健壮)
            // 如果读取失败 (例如摄像头断开)
            emit statusChanged("错误: 无法从摄像头读取帧！");
            QThread::msleep(1000); // 休息 1 秒
            continue; 
        }

        if (frame_1080p.empty()) {
            QThread::msleep(10); // (给 CPU 一点休息时间)
            continue; 
        }
        //缩小原图像
        cv::Mat smallFrame;
        const float targetWidth = 640.0;
        float scale = targetWidth / frame_1080p.cols;
        cv::resize(frame_1080p, smallFrame, cv::Size(), scale, scale, cv::INTER_LINEAR);
        // --- 复制结束 ---
        if (m_snapshotRequested)
        {
            m_snapshotRequested = false; // (重置标志)
            
            // (冻结) 把这一帧保存到 m_lastCleanFrame
            m_lastCleanFrame = smallFrame.clone(); // (克隆一份 *干净* 的帧)
            
            // (发送) 把“冻结”的帧发给 UI 作为“预览”
            emit snapshotReady(convertMatToQImage(m_lastCleanFrame));
            
            emit statusChanged("抓拍成功！准备录入。");
        }

        // a. 调用后端引擎 (已优化，不再卡顿)
        RecognitionResult result = m_processor.processFrame(smallFrame);
        //硬件调用
        handleHardwareTrigger(result);

        // b. (后端绘制) 在帧上绘制结果
        // (UI 线程不需要再做任何绘制)
        if (result.is_foundface) {
            // 画方框
            cv::rectangle(smallFrame, result.face_position, cv::Scalar(0, 255, 0), 2);
            
            // 准备两行文本
            std::string name_text = result.name;
            std::stringstream ss;
            ss << "Dist: " << std::fixed << std::setprecision(1) << result.confidence;
            std::string conf_text = ss.str();
            
            // 计算位置
            cv::Point confPos(result.face_position.x, result.face_position.y - 30); 
            cv::Point namePos(result.face_position.x, result.face_position.y - 10); 

            // 画上去
            cv::putText(smallFrame, conf_text, confPos, cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
            cv::putText(smallFrame, name_text, namePos, cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
        }

        // c. 发射信号，把结果 (QImage) 发给 UI 线程
        QImage qImg = convertMatToQImage(smallFrame);
        emit frameReady(qImg.copy()); // (必须 .copy() 保证线程安全)
    }

    m_cap.release();
    emit statusChanged("处理已停止。");
}

/**
 * @brief (槽) 停止循环。
 * (这是一个线程安全的槽，可以从 UI 线程调用)
 */
void FaceWorker::stopProcessing()
{
    m_isRunning = false; // 告诉 while 循环停止
}

/**
 * @brief (槽) 抓拍快照 (替代 capture_tool)。
 * (这个槽会被 UI 线程的信号触发，但在工作线程中执行)
 */
void FaceWorker::captureSnapshot()
{
    if (!m_isRunning) {
        emit statusChanged("错误: 摄像头未运行，无法抓拍。");
        return;
    }
    m_snapshotRequested = true;

}


void FaceWorker::checkIdAvailability(const QString& id_str)
{
    bool ok;
    int id = id_str.toInt(&ok);

    if (!ok || id < 0) {
        emit idStatusReady(false); // (不是有效数字，也算“不可用”)
        return;
    }

    // (调用引擎的 "isIdRegistered" 检查)
    bool isAvailable = !m_processor.isIdRegistered(id);
    
    // (把结果发回给 UI)
    emit idStatusReady(isAvailable);
}



/**
 * @brief (槽) 录入已抓拍的人脸
 */
void FaceWorker::enrollCapturedFace(int employeeId, const QString& employeeName)
{
    if (m_lastCleanFrame.empty()) {
        emit statusChanged("错误: 没有可录入的快照。请先抓拍。");
        return;
    }
    if (employeeName.isEmpty() || employeeId < 0) {
        emit statusChanged("错误: ID 或姓名无效。");
        return;
    }

    emit statusChanged(QString("正在录入 ID: %1, 姓名: %2...").arg(employeeId).arg(employeeName));
    
    // ---检测并裁剪 ---
    // 在 m_lastCleanFrame 上操作
    cv::Mat gray;
    cv::cvtColor(m_lastCleanFrame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    // 临时检测器)
    cv::CascadeClassifier faceDetector; 
    const std::string cascadePath = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
    if (!faceDetector.load(cascadePath)) {
        emit statusChanged("错误: 无法加载检测器 (enroll)。");
        return;
    }

    std::vector<cv::Rect> faces;
    faceDetector.detectMultiScale(gray, faces, 1.2, 5, 0, cv::Size(80, 80));

    if (faces.empty()) {
        emit statusChanged("录入失败: 抓拍的快照中未检测到人脸！");
        return;
    }

    cv::Mat faceROI = gray(faces[0]);

    // --- 调用引擎 ---
    // (优化的、带 std::map 的 m_processor)
    bool success = m_processor.enrollNewFace(faceROI, employeeId, employeeName.toStdString());

    if (success) {
        emit statusChanged(QString("录入成功: ID %1 已保存！").arg(employeeId));
    } else {
        emit statusChanged("录入失败: ID %1 可能已经存在！");
    }
    m_lastCleanFrame.release();
}


/**
 * @brief (辅助函数) cv::Mat -> QImage
 * 将 OpenCV (BGR) 转换为 Qt (RGB)
 */
QImage FaceWorker::convertMatToQImage(const cv::Mat& mat)
{
    // 检查输入是否有效
    if(mat.empty())
        return QImage();

    // 3 通道 (BGR) 图像
    if (mat.type() == CV_8UC3) {
        cv::Mat rgb;
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
        // (QImage::Format_RGB888 要求数据是 RGB 顺序)
        QImage temp_shallow_copy(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
        return temp_shallow_copy.copy();
    } 
    // 1 通道 (灰度) 图像
    else if (mat.type() == CV_8UC1) {
        QImage temp_shallow_copy(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        return temp_shallow_copy.copy();
    }
    
    // (其他格式暂不支持)
    qWarning() << "FaceWorker::convertMatToQImage - 不支持的 cv::Mat 类型: " << mat.type();
    return QImage(); 
}
 void FaceWorker::handleHardwareTrigger(const RecognitionResult& result)
 {
    if (result.is_known)
    {
        if (result.person_id !=m_lastRecognizedId)
        {
            emit recognitionResultReady(result);

            m_lastRecognizedId=result.person_id;

            m_hardwareController.triggerSuccessSequence(result.person_id);
        }
        
    }
    else 
    {
        // (重置状态)
        m_lastRecognizedId = -1;
    }
 }