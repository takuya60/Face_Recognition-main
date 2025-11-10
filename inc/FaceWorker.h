#pragma once

#include <QObject>
#include <QString>
#include <QImage>       // (用于向 UI 传递图像)
#include <QThread>      // (我们会把它移到 QThread)
#include "face_opencv.h" // (或 face_opencv.h, 包含你的“引擎”)

/**
 * @brief (重要) 注册 RecognitionResult 结构体
 * 允许它在 Qt 的信号-槽机制中被安全地传递。
 * UI) *必须* 在他的 main.cpp 或 MainWindow.cpp 中包含 face_opencv.h 和这行代码。
 */
Q_DECLARE_METATYPE(RecognitionResult);


/**
 * @brief 后端控制器 (API)
 * 这是一个 QObject, 它封装了所有的 OpenCV 逻辑。
 * 它将被移动到一个单独的 QThread 中运行，以防止 UI 线程被冻结。
 */
class FaceWorker : public QObject
{
    Q_OBJECT // (Qt 的宏，必须有)

public:
    explicit FaceWorker(QObject *parent = nullptr);
    ~FaceWorker();

private:
    face_processor m_processor; // 你的“引擎”
    cv::VideoCapture m_cap;     // 摄像头
    
    /**
     * @brief (关键) 线程安全的停止标志
     * 'volatile' 确保所有线程都能看到它的最新值。
     */
    volatile bool m_isRunning;  
    
    /**
     * @brief 抓拍请求标志
     * UI 线程会把它设为 true, 工作线程会检查它。
     */
    volatile bool m_snapshotRequested;

    /**
     * @brief (关键) 快照存储
     * 抓拍时，将干净的帧保存在这里。
     */
    cv::Mat m_lastCleanFrame; 

    /**
     * @brief (辅助函数) cv::Mat -> QImage
     * 将 OpenCV 的 BGR 图像转换为 Qt 的 RGB 图像。
     */
    QImage convertMatToQImage(const cv::Mat& mat);

public slots:
    // --- 这是 UI 可以 *调用* 的接口 ---
    
    /**
     * @brief (槽) 开始实时处理循环。
     * UI 通过调用此槽来启动摄像头和识别。
     * @param deviceId 摄像头的 ID (例如 /dev/video1 对应的 1)
     */
    void startProcessing(int deviceId);
    
    /**
     * @brief (槽) 请求停止实时处理循环。
     * 这是一个线程安全的函数，可以从 UI 线程调用。
     */
    void stopProcessing();

    /**
     * @brief (槽) 响应 UI 的“抓拍”按钮 (替代 capture_tool)。
     * 它会把当前帧保存到 m_lastCleanFrame 中，并发出 snapshotReady 信号。
     */
    void captureSnapshot();

    /**
     * @brief (槽) 响应 UI 的“录入”按钮 (替代 enroll_tool)。
     * 它会使用 m_lastCleanFrame，并调用引擎的 enrollNewFace。
     * @param employeeId  从 UI 输入框获取的 ID
     * @param employeeName 从 UI 输入框获取的 Name
     */
    void enrollCapturedFace(int employeeId, const QString& employeeName);

signals:
    // --- 这是 UI 可以 *接收* 的接口 ---

    /**
     * @brief (信号) 当一帧处理完毕并准备好显示时发出。
     * (后端已经在这张 QImage 上画好了框和名字)
     */
    void frameReady(const QImage& frame);

    /**
     * @brief (信号) 当抓拍成功时，发送一张“快照”给 UI。
     * (UI 可以在一个小 QLabel 里显示这张*未绘制*的快照作为预览)
     */
    void snapshotReady(const QImage& snapshot);

    /**
     * @brief (信号) 当状态或错误发生时发出。
     * (例如: "摄像头已打开", "初始化失败!", "录入成功!")
     */
    void statusChanged(const QString& message);
};