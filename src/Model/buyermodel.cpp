#include "buyermodel.h"

BuyerModel::BuyerModel(ConnectionHandler* connectionHandler) : BaseModel(connectionHandler)
{}

QList<ElementPeople*>& BuyerModel::updateInfoBuyPeople(QWidget* parent)
{
    updateModelViaQuery("select inn, full_name, phone_number, city from buyer join address using(id_address) order by id_address");

    list.clear();
    for (int i = 0; i < modelData->rowCount(); ++i)
        list.append(new ElementPeople(modelData->index(i, 0).data().toString(),
                                      modelData->index(i, 1).data().toString(),
                                      modelData->index(i, 2).data().toString(),
                                      modelData->index(i, 3).data().toString(), connection, parent));

    return list;
}

void BuyerModel::setHeaderModel()
{}
