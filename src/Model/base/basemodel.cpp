#include "basemodel.h"
#include <QSqlError>
#include <QException>

BaseModel::BaseModel(ConnectionHandler* connection) :
    connection(connection)
{
    modelData = new QSqlRelationalTableModel(nullptr, *connection->getDB());
    modelData->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
}

QSqlRelationalTableModel* BaseModel::getModelData() { return modelData; }

bool BaseModel::updateModel(QString table, QString filter, int column, const QSqlRelation& relation)
{
    modelData->setTable(table);

    if(relation.isValid())
        modelData->setRelation(column, relation);

    if(filter != "")
        modelData->setFilter(filter);

    bool isOk = modelData->select();
    setHeaderModel();

    return isOk;
}

bool BaseModel::updateModelViaQuery(QString request)
{
    QSqlQuery query(request, *connection->getDB());

    if(query.exec())
    {
        modelData->clear();
        modelData->setQuery(std::move(query));
        return true;
    }

    return false;
}

QSqlQuery* BaseModel::select(const QString& request)
{
    QSqlQuery* query = new QSqlQuery(request, *connection->getDB());

    if(query->exec())
        return query;

    delete query;
    return nullptr;
}

QString BaseModel::getOneCell(const QString& request)
{
    QSqlQuery* query = new QSqlQuery(request, *connection->getDB());

    if(query->exec())
    {
        if(query->first())
        {
            QString ret = query->value(0).toString();
            delete query;
            return ret;
        }
    }

    delete query;
    return "";
}

bool BaseModel::requestBD(QString request)
{
    QSqlQuery query(*connection->getDB());
    query.prepare(request);
    bool ok = query.exec();
    lastInsertId = query.lastInsertId().toInt();
    return ok;
}

BaseModel::~BaseModel()
{
    delete modelData;
}
