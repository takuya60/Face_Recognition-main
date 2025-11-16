#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include "FaceWorker.h"
#include <QMainWindow>
#include <QVector>
#include <QThread>
#include <QObject>
#include "log_thread.h"
#include "ui.h"

QT_BEGIN_NAMESPACE
namespace UI { class Face; }
QT_END_NAMESPACE

class Face : public QMainWindow
{
    Q_OBJECT
public:
    Face(QWidget *parent = nullptr);
    ~Face();
private slots:
    void showLogs(QVector<log_info> logs);
    void showImage(const QImage&  frame);
    void showMessage(const QString& message);
    void facePass(const RecognitionResult& result);
    void showSnapshotWidget(const QImage& shapshot);
signals:
    void read_notification(int len);
    void open_camera_notification(int deviceId);
    void stop_camera_notification();
    void write_log_notification(const log_info& log);
    void enroll_new_face_notification(int employeeID,const QString& employeeName);
private:
    UI::Face* ui;
    
    QThread writeLogThread;
    QThread readLogThread;
    QThread faceWorkerThread;

    FaceWorker *face_worker; 
    LogDatabase *logdb;
    WriteLog *write_log;
    ReadLog *read_log;

};

#endif // _MAIN_WINDOW_H_
