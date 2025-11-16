#include "main_window.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication face_app(argc,argv);
    Face win;
    win.show();
    return face_app.exec();

}
