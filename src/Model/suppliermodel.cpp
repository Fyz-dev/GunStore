#include "suppliermodel.h"

SupplierModel::SupplierModel(ConnectionHandler* connection) : BaseModel(connection)
{}

void SupplierModel::setHeaderModel()
{
    modelData->setHeaderData(1, Qt::Horizontal, "Назва фірми");
    modelData->setHeaderData(2, Qt::Horizontal, "Код ЄДРПОУ");
    modelData->setHeaderData(3, Qt::Horizontal, "Номер телефону");
    modelData->setHeaderData(4, Qt::Horizontal, "Адреса ");
    modelData->setHeaderData(5, Qt::Horizontal, "Розрахунковий рахунок");
}


void SupplierModel::addToRomove(const int& row)
{
    int idProduct = modelData->index(row, 0).data().toInt();

    if(!listToRemove.contains(idProduct))
        listToRemove.append(idProduct);
    else
        listToRemove.removeOne(idProduct);
}

