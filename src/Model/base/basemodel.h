#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>

class BaseModel
{
public:
    BaseModel(QSqlDatabase* db);
    virtual ~BaseModel();

public:
    QSqlRelationalTableModel* getModelData();
    virtual bool updateModel(QString table, QString filter = "", int colum = 0, const QSqlRelation& relation = QSqlRelation());
    virtual bool updateModelViaQuery(QString request);
    virtual bool requestBD(QString request);
    const int& getLastInsertId() { return lastInsertId; }

protected:
    virtual void setHeaderModel() = 0;
    QSqlQuery* select(const QString& request);

protected:
    QSqlDatabase* db;
    QSqlRelationalTableModel* modelData;
    int lastInsertId;
};

#endif // BASEMODEL_H
