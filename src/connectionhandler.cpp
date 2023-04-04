#include "connectionhandler.h"
#include <QDebug>

ConnectionHandler::ConnectionHandler()
{
    this->db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
}

bool ConnectionHandler::connectionDataBase(QString userName, QString password)
{
    db->setDatabaseName("gunstore");
    db->setHostName("127.0.0.1");
    db->setUserName(userName);
    db->setPassword(password);
    db->setPort(3306);

    return dbOpen = db->open();
}

QSqlDatabase* ConnectionHandler::getDB() { return db; }

ConnectionHandler::~ConnectionHandler()
{
    if(dbOpen)
        db->close();
    delete db;
}
