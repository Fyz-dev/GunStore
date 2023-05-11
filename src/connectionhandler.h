#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QSqlDatabase>

class ConnectionHandler
{
public:
    ConnectionHandler();
    ~ConnectionHandler();

public:
    bool connectionDataBase(QString userName, QString password);
    QSqlDatabase* getDB();
    const QString& getIdWorker() { return idWorker; }
    const QString& getPosition() { return position; }

private:
    QSqlDatabase* db;
    QString idWorker;
    QString position;
    bool dbOpen = false;
};

#endif // CONNECTIONHANDLER_H
