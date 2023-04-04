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

private:
    QSqlDatabase* db;
    bool dbOpen = false;
};

#endif // CONNECTIONHANDLER_H
