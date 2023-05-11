#include "connectionhandler.h"
#include <QSqlQuery>

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

    if((dbOpen = db->open()))
    {
        QSqlQuery query;
        query.exec("select id_worker, `position` from worker where w_full_name = '" + userName + "'");
        if(query.first())
        {
            idWorker = query.value(0).toString();
            position = query.value(1).toString();
        }

        qDebug() << position;
    }

    return dbOpen;
}

QSqlDatabase* ConnectionHandler::getDB() { return db; }

ConnectionHandler::~ConnectionHandler()
{
    if(dbOpen)
        db->close();
    delete db;
}
