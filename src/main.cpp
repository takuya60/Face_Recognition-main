#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QImage>

#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {

    cv::Mat Image;
    QApplication a(argc,argv);
    QLabel label("Hello form i.MAX6ULL + Qt!");
    label.resize(300,80);
    label.show();
    return a.exec();

}