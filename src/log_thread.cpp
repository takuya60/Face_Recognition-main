#include "log_thread.h"
#include <QVariant>

#define DATABASE_FILE "/mnt/tf/recognition.db"

static QSqlDatabase db;

LogDatabase::LogDatabase(const QString& file) {
    db = QSqlDatabase::addDatabase("QSQLITE","LogDatabase");
    db.setDatabaseName(file);
    db.open();

    QSqlQuery q(db);
    q.exec(
        "CREATE TABLE IF NOT EXISTS log("           \
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"     \
        "TIME TEXT,"                                \
        "USER TEXT,"                                \
        "PASSED TEXT)");
}

LogDatabase::~LogDatabase() {
    db.close();
    QSqlDatabase::removeDatabase("LogDatabase");
}

void WriteLog::writeLog(const log_info& log) {
    QSqlQuery q(db);
    q.prepare("INSERT INTO log(TIME,USER,PASSED) VALUES(datetime('now'),?,?)");
    q.addBindValue(log.user);
    q.addBindValue(log.passed);
    q.exec();
}

void ReadLog::readNextPageLogs(int len) {
    QVector<log_info> result;
    QSqlQuery q(db);

    q.prepare(
        "SELECT id,TIME,USER,PASSED FROM log " \
        "ORDER BY id DESC LIMIT ? OFFSET ?");
    q.addBindValue(len);
    q.addBindValue(this->offset);
    q.exec();

    while (q.next()) {
        result.push_back(log_info{
            q.value(0).toInt(),
            q.value(1).toString(),
            q.value(2).toString(),
            q.value(3).toString()
        });
    }

    if (result.size() == len) {
        this->offset += len;
    }
    else {
        this->offset = 0;
    }

    emit LogsReady(result);
}



