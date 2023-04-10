#include "basemodel.h"

BaseModel::BaseModel(QSqlDatabase* db) :
    db(db)
{
    modelData = new QSqlTableModel(nullptr, *db);
}

QSqlTableModel* BaseModel::getModelData() { return modelData; }

bool BaseModel::updateModel(QString request)
{
    QSqlQuery query(request, *db);

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
    QSqlQuery* query = new QSqlQuery(request, *db);

    if(query->exec())
        return query;

    delete query;
    return nullptr;
}

bool BaseModel::updateInfoBD(QString request)
{
    QSqlQuery query(*db);
    query.prepare(request);
    return query.exec();
}

BaseModel::~BaseModel()
{
    delete modelData;
}
