#include "basemodel.h"

BaseModel::BaseModel(QSqlDatabase* db) :
    db(db)
{
    modelData = new QSqlTableModel;
}

QSqlTableModel* BaseModel::getModelData() { return modelData; }

bool BaseModel::updateModel(QString request)
{
    QSqlQuery query;
    query.prepare(request);

    if(query.exec())
    {
        modelData->clear();
        modelData->setQuery(std::move(query));
        return true;
    }

    return false;
}

QSqlQuery* BaseModel::select(QString request)
{
    QSqlQuery* query = new QSqlQuery;
    query->prepare(request);

    if(query->exec())
    {
        return query;
    }

    delete query;
    return nullptr;
}

BaseModel::~BaseModel()
{
    delete modelData;
}
