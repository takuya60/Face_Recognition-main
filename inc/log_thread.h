#ifndef LOG_THREAD_H
#define LOG_THREAD_H

#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QString>

struct log_info {
    int id;
    QString time;
    QString user;
    QString passed;
};

class LogDatabase {
public:
    LogDatabase(const QString& file);
    ~LogDatabase();
};

class WriteLog : public QObject {
    Q_OBJECT
public:
    explicit WriteLog(QObject* parent = nullptr) : QObject(parent){};
public slots:
    void writeLog(const log_info& log);
};

class ReadLog : public QObject {
    Q_OBJECT
public:
    explicit ReadLog(QObject* parent = nullptr) : QObject(parent){};
public slots:
    void readNextPageLogs(int len);
signals:
    void LogsReady(QVector<log_info> show_infos);
private:
    int offset = 0;

};


#endif //LOG_THREAD_H
