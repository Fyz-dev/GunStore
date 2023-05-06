#include "employeesmodel.h"
#include <QSqlQuery>

EmployeesModel::EmployeesModel(ConnectionHandler* connection) : BaseModel(connection)
{}

void EmployeesModel::setHeaderModel()
{
//    modelData->setHeaderData(1, Qt::Horizontal, "ФІО");
//    modelData->setHeaderData(2, Qt::Horizontal, "Позиція");
//    modelData->setHeaderData(3, Qt::Horizontal, "Номер телефону");
//    modelData->setHeaderData(4, Qt::Horizontal, "Адреса");
//    modelData->setHeaderData(5, Qt::Horizontal, "Стать");
//    modelData->setHeaderData(6, Qt::Horizontal, "День народження");
}

QList<ElementPeople*>& EmployeesModel::updateInfoBuyPeople(QWidget* parent)
{
    updateModelViaQuery("select id_worker, w_full_name, `position`, w_phoneNum, SUBSTRING_INDEX(w_address, ', ', 1) from worker;");

    list.clear();
    for (int i = 0; i < modelData->rowCount(); ++i)
        list.append(new ElementPeople(modelData->index(i, 0).data().toString(),
                                      modelData->index(i, 1).data().toString(),
                                      modelData->index(i, 2).data().toString(),
                                      modelData->index(i, 3).data().toString(),
                                      modelData->index(i, 4).data().toString(),
                                      parent, connection));

    return list;
}
