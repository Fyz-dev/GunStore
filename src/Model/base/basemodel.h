#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

class BaseModel
{
public:
    BaseModel(QSqlDatabase* db);
    ~BaseModel();

public:
    QSqlTableModel* getModelData();
    virtual bool updateModel(QString request);

protected:
    QSqlQuery* select(QString request);
    QString s;

protected:
    QSqlDatabase* db;
    QSqlTableModel* modelData;
};

#endif // BASEMODEL_H
