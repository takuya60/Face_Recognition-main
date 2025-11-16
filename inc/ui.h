#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDialog>
#include <QLineEdit>

class Face_UI {

public:
    QStackedWidget *Page;

    QWidget *page_face;
    QLabel *face_label;

    QWidget *page_log;
    QTableWidget *log_table;
    QPushButton *btn_next;

    QWidget *page_new_face;
    QLabel *new_face_label;
    QPushButton *btn_face;
    QPushButton *btn_log;
    QPushButton *btn_new;
    QPushButton *btn_ok;
    QDialog* snapshot_dialog;
    QLabel *snapshot;
    QPushButton *snap_enroll;
    QPushButton *snap_delet;
    QLineEdit *name_edit;
    QLineEdit *id_edit;

    void setupUI(QMainWindow* Face) {
        Face->setObjectName("Face");
        Face->setFixedSize(480,800);

        QWidget *central = new QWidget(Face);
        QVBoxLayout *mainLayout = new QVBoxLayout(central);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        Face->setCentralWidget(central);

        //Page
        Page = new QStackedWidget(Face);
        mainLayout->addWidget(Page);

        // Page0:Face Recognition
        page_face = new QWidget();
        QVBoxLayout *faceLayout = new QVBoxLayout(page_face);

        face_label = new QLabel("实时摄像头画面区域", page_face);
        face_label->setAlignment(Qt::AlignCenter);
        face_label->setScaledContents(true);
        face_label->setStyleSheet(
                    "background:#000;color:white;font-size:20px;");

        faceLayout->addWidget(face_label);
        Page->addWidget(page_face);

        //Page1:Log Page
        page_log = new QWidget();
        QVBoxLayout *logLayout = new QVBoxLayout(page_log);

        log_table = new QTableWidget(10, 3, page_log);
        log_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        log_table->setSelectionMode(QAbstractItemView::NoSelection);
        log_table->setShowGrid(true);

        QStringList headers;
        headers << "时间" << "人员" << "结果";
        log_table->setHorizontalHeaderLabels(headers);
        log_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        log_table->verticalHeader()->setVisible(false);

        log_table->setStyleSheet(
                "QTableWidget { "                                       \
                "background:#f8f8f8; font-size:16px; }"                 \
                "QHeaderView::section { "                               \
                "background:#e0e0e0; font-weight:bold; }"               \
                );

        btn_next = new QPushButton("下一页", page_log);
        btn_next->setFixedHeight(50);
        btn_next->setStyleSheet(
                "QPushButton  {"                                        \
                " background:#2196F3; "                                 \
                "color:white; border-radius:8px; font-size:18px; }"     \
                "QPushButton:pressed { background:#1976D2; }"           \
                );

        logLayout->addWidget(log_table);
        logLayout->addWidget(btn_next);
        Page->addWidget(page_log);

        //Page2:New Face
        page_new_face = new QWidget();
        QVBoxLayout *newFaceLayout = new QVBoxLayout(page_new_face);

        new_face_label = new QLabel("录入新的人脸画面区域", page_new_face);
        new_face_label->setAlignment(Qt::AlignCenter);
        new_face_label->setScaledContents(true);
        new_face_label->setStyleSheet(
                    "background:#000;color:white;font-size:20px;");

        btn_ok = new QPushButton("抓拍", page_new_face);
        btn_ok->setFixedHeight(60);
        btn_ok->setStyleSheet(
                "QPushButton { "                                \
                "background:#4CAF50; color:white; "             \
                "border-radius:8px; font-size:20px; }"          \
                "QPushButton:pressed { background:#3E8E41; }"   \
                );

        newFaceLayout->addWidget(new_face_label);
        newFaceLayout->addWidget(btn_ok);
        Page->addWidget(page_new_face);

        snapshot_dialog = new QDialog(page_new_face);
        QVBoxLayout *dialog_lay = new QVBoxLayout(snapshot_dialog);
        snapshot = new QLabel("抓拍",snapshot_dialog);
        snapshot->setAlignment(Qt::AlignCenter);
        snapshot->setScaledContents(true);
        snapshot->setStyleSheet(
                "background:#000;color:white;font-size:20px;");
        dialog_lay->addWidget(snapshot);
        name_edit = new QLineEdit(snapshot_dialog);
        name_edit->setPlaceholderText("name:");
        id_edit = new QLineEdit(snapshot_dialog);
        id_edit->setPlaceholderText("id:");
        dialog_lay->addWidget(id_edit);
        dialog_lay->addWidget(name_edit);
        QHBoxLayout *snap_btn_lay = new QHBoxLayout(snapshot_dialog);
        snap_enroll = new QPushButton("确认",snapshot_dialog);
        snap_enroll->setFixedHeight(40);
        snap_enroll->setStyleSheet(
                "QPushButton { "                                \
                "background:#4CAF50; color:white; "             \
                "border-radius:8px; font-size:20px; }"          \
                "QPushButton:pressed { background:#3E8E41; }"   \
                );
        snap_delet = new QPushButton("取消",snapshot_dialog);
        snap_delet->setFixedHeight(40);
        snap_delet->setStyleSheet(
                "QPushButton { "                                \
                "background:#4CAF50; color:white; "             \
                "border-radius:8px; font-size:20px; }"          \
                "QPushButton:pressed { background:#3E8E41; }"   \
                );
        snap_btn_lay->addWidget(snap_enroll);
        snap_btn_lay->addWidget(snap_delet);
        dialog_lay->addLayout(snap_btn_lay);

        //Menu Bar
        QWidget *topBar = new QWidget(Face);
        topBar->setFixedHeight(70);
        topBar->setStyleSheet("background:#303030;");
        mainLayout->addWidget(topBar);

        QHBoxLayout *topLayout = new QHBoxLayout(topBar);
        topLayout->setContentsMargins(10, 5, 10, 5);
        topLayout->setSpacing(10);

        btn_face = new QPushButton("识别");
        btn_log = new QPushButton("日志");
        btn_new = new QPushButton("录入");

        QString btnStyle = 
            "QPushButton {"             \
            "   background:#87CEFA;"    \
            "   color:white;"           \
            "   border-radius:10px;"    \
            "   font-size:26px;"        \
            "   padding:10px;"          \
            "}"                         \
            "QPushButton:pressed {"     \
            "   background:#1E90FF;"    \
            "}";

        btn_face->setStyleSheet(btnStyle);
        btn_log->setStyleSheet(btnStyle);
        btn_new->setStyleSheet(btnStyle);

        topLayout->addWidget(btn_face);
        topLayout->addWidget(btn_log);
        topLayout->addWidget(btn_new);

        Page->setCurrentIndex(0);

    }
};

namespace UI {
    class Face:public Face_UI {};
}

#endif // _UI_H_
