#include "suppliermodel.h"

SupplierModel::SupplierModel(ConnectionHandler* connection) : BaseModel(connection)
{}

void SupplierModel::setHeaderModel()
{
//    modelData->setHeaderData(1, Qt::Horizontal, "Назва фірми");
//    modelData->setHeaderData(2, Qt::Horizontal, "Код ЄДРПОУ");
//    modelData->setHeaderData(3, Qt::Horizontal, "Номер телефону");
//    modelData->setHeaderData(4, Qt::Horizontal, "Адреса ");
//    modelData->setHeaderData(5, Qt::Horizontal, "Розрахунковий рахунок");
}

QList<ElementPeople*>& SupplierModel::updateInfoBuyPeople(QWidget* parent, const QString& isDelete)
{
    updateModelViaQuery(QString("select id_supplier, sup_name, sup_edrpou, sup_phoneNum, SUBSTRING_INDEX(sup_address, ', ', 1) from supplier where isDelete = %1").arg(isDelete));

    for(ElementPeople* item : list)
        delete item;
    list.clear();

    for (int i = 0; i < modelData->rowCount(); ++i)
        list.append(new ElementPeople(modelData->index(i, 0).data().toString(),
                                      modelData->index(i, 1).data().toString(),
                                      modelData->index(i, 2).data().toString(),
                                      modelData->index(i, 3).data().toString(),
                                      modelData->index(i, 4).data().toString(),
                                      connection, parent));

    return list;
}
