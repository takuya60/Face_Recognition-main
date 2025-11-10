#include <opencv2/opencv.hpp>
#include "face_opencv.h"
#include <iostream>
#include <stdio.h>
#include <sstream>      // 用于格式化字符串
#include <iomanip>      // 用于设置小数精度

using namespace std;
int main()
{

    face_processor processor;
    string cascadePath="/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
    if(! processor.initialize(cascadePath))
    {
        cerr<<"初始化失败，模型路径："<<cascadePath<<endl;
        return -1;
    }
    cv::VideoCapture cap(0);
    if(! cap.isOpened())
    {
        cerr<<"摄像头无法打开"<<endl;
        return -1;
    }


    while (true)
    {
        cv::Mat frame;
        cap>>frame;
        if(frame.empty())
        break;

        RecognitionResult result=processor.processFrame(frame);
        if (result.is_foundface)
            {
                cv::rectangle(frame, result.face_position, cv::Scalar(0, 255, 0), 2);
                // 名字
                std::string name_text = result.name;

                // 置信度 (需要格式化)
                std::stringstream ss;
                // "Dist:"(距离) << "保留1位小数" << [置信度值]
                ss << "Dist: " << std::fixed << std::setprecision(1) << result.confidence;
                std::string conf_text = ss.str();

                // --- 3. 计算两行文本的位置 ---
                int pos_x = result.face_position.x;
                int pos_y = result.face_position.y;

                // (我们把字号调小到 0.7，因为两行字需要更多空间)
                // 置信度 (在上面一行): 距离方框顶部 30 像素
                cv::Point confPos(pos_x, pos_y - 30); 

                // 名字 (在下面一行): 距离方框顶部 10 像素
                cv::Point namePos(pos_x, pos_y - 10); 

                // --- 4. 画出两行文本 ---
                cv::putText(frame, conf_text, confPos, cv::FONT_HERSHEY_SIMPLEX, 
                            0.7, // 字号
                            cv::Scalar(0, 255, 0), 2); // 绿色

                cv::putText(frame, name_text, namePos, cv::FONT_HERSHEY_SIMPLEX, 
                            0.7, // 字号
                            cv::Scalar(0, 255, 0), 2); // 绿色
            }
        cv::imshow("Face Recognition",frame);
        int key = cv::waitKey(30);
        if (key == 27) // 27 是 ESC 键
        {
            cout << "[INFO] 按下 ESC 退出..." << endl;
            break; 
        }
    }
    return 0;
}