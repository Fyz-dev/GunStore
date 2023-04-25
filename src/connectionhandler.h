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

private:
    QSqlDatabase* db;
    QString idWorker;
    bool dbOpen = false;
};

#endif // CONNECTIONHANDLER_H
