#include "main_window.h"
#include "FaceWorker.h"
#include "log_thread.h"
#include <QString>
#include <QDialog>
#include <QDebug>

Face::Face(QWidget *parent)
    : QMainWindow(parent)
    , ui(new UI::Face)
{
    ui->setupUI(this);
        
    //日志数据库的读写部分
    logdb = new LogDatabase("/mnt/tf/recognition_log.db");
    write_log = new WriteLog;
    read_log = new ReadLog;

    write_log->moveToThread(&writeLogThread);
    read_log->moveToThread(&readLogThread);

    writeLogThread.start();
    readLogThread.start();

    //摄像机部分
    face_worker = new  FaceWorker;

    face_worker->moveToThread(&faceWorkerThread);

    faceWorkerThread.start();

    connect(ui->btn_face, &QPushButton::clicked, 
            this, [=](){ ui->Page->setCurrentIndex(0); 
                         emit open_camera_notification(2);});
    connect(ui->btn_log, &QPushButton::clicked, 
            this, [=](){ ui->Page->setCurrentIndex(1); 
                         emit stop_camera_notification();
                         //zhao
                         emit read_notification(10);});
    connect(ui->btn_new, &QPushButton::clicked, 
            this, [=](){ ui->Page->setCurrentIndex(2); 
                         emit open_camera_notification(2);});
    connect(ui->snap_delet, &QPushButton::clicked,
            this, [=](){ui->snapshot_dialog->close();});
    connect(ui->snap_enroll, &QPushButton::clicked,
            this, [=](){
            emit Face::enroll_new_face_notification(
                    ui->id_edit->text().toInt(),
                    ui->name_edit->text());
            //zhao
            ui->snapshot_dialog->close(); 
            });
                    
    //点击下一页发送读日志申请
    connect(ui->btn_next, &QPushButton::clicked,
            this, [=](){ emit read_notification(10); });
    //绑定读日志申请与读日志
    connect(this, &Face::read_notification,
            read_log, &ReadLog::readNextPageLogs);
    //读取完成显示ui
    connect(read_log, &ReadLog::LogsReady, 
            this, &Face::showLogs);
    //收到写信号进行写日志
    connect(this,&Face::write_log_notification,
            write_log,&WriteLog::writeLog);
    //识别到人脸显示图片
    connect(face_worker, &FaceWorker::frameReady,
            this, &Face::showImage);
    //状态改变显示消息
    connect(face_worker, &FaceWorker::statusChanged,
            this, &Face::showMessage);
    //认证成功发送信号
    connect(face_worker, &FaceWorker::recognitionResultReady,
            this, &Face::facePass);
    //发送开始识别的请求
    connect(this, &Face::open_camera_notification,
            face_worker, &FaceWorker::startProcessing);
    //发送结束识别的请求
    connect(this, &Face::stop_camera_notification,
            face_worker, &FaceWorker::stopProcessing);
    //确认抓拍
    connect(ui->btn_ok,&QPushButton::clicked,
            face_worker,&FaceWorker::captureSnapshot);
    //获得抓拍照后弹出输入信息和确认窗口
    connect(face_worker,&FaceWorker::snapshotReady,
            this,&Face::showSnapshotWidget);

    //zhao
    //录入确认
    connect(this, &Face::enroll_new_face_notification,
            face_worker, &FaceWorker::enrollCapturedFace);
    connect(ui->btn_ok,&QPushButton::clicked,
            face_worker,&FaceWorker::captureSnapshot);

}

Face::~Face()
{
    delete ui;
    delete logdb;
    writeLogThread.quit();
    writeLogThread.wait();
    readLogThread.quit();
    readLogThread.wait();
    faceWorkerThread.quit();
    faceWorkerThread.wait();
}

void Face::showLogs(QVector<log_info> logs) {
    ui->log_table->clearContents();
    for (int i = 0; i < logs.size(); i++) {
        ui->log_table->setItem(i,0,new QTableWidgetItem(logs[i].time));
        ui->log_table->setItem(i,1,new QTableWidgetItem(logs[i].user));
        ui->log_table->setItem(i,2,new QTableWidgetItem(logs[i].passed));
    }
}

void Face::showImage(const QImage& frame) {
    ui->face_label->setPixmap(QPixmap::fromImage(frame));
    ui->face_label->setScaledContents(true);

    //zhao
    ui->new_face_label->setPixmap(QPixmap::fromImage(frame));
    ui->new_face_label->setScaledContents(true);
}

void Face::facePass(const RecognitionResult& result) {
    log_info* log = new log_info;
    log->passed = "Pass";
    log->user = QString::fromStdString(result.name);
    emit write_log_notification(*log);
}

void Face::showMessage(const QString& message) {
    qDebug() << "message:" << message << "\n";
}

void Face::showSnapshotWidget(const QImage& snap) {
    ui->snapshot->setPixmap(QPixmap::fromImage(snap));
    ui->snapshot->setScaledContents(true);
    ui->snapshot_dialog->show();
        
}


