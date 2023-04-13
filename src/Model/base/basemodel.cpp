#include "basemodel.h"

BaseModel::BaseModel(QSqlDatabase* db) :
    db(db)
{
    modelData = new QSqlRelationalTableModel(nullptr, *db);
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

    if(modelData->select())
    {
        setHeaderModel();
        return true;
    }

    return false;
}

bool BaseModel::updateModelViaQuery(QString request)
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

bool BaseModel::requestBD(QString request)
{
    QSqlQuery query(*db);
    query.prepare(request);
    return query.exec();
}

BaseModel::~BaseModel()
{
    delete modelData;
}
