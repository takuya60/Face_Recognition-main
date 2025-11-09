#include <opencv2/opencv.hpp>
#include "face_opencv.h"
#include <iostream>
#include <stdio.h>

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
            cv::putText(frame, result.name, result.face_position.tl(),
                        cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
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
};