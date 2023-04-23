#include "employeesmodel.h"
#include <QSqlQuery>

EmployeesModel::EmployeesModel(QSqlDatabase* db) : BaseModel(db)
{}

void EmployeesModel::setHeaderModel()
{
    modelData->setHeaderData(1, Qt::Horizontal, "ФІО");
    modelData->setHeaderData(2, Qt::Horizontal, "Позиція");
    modelData->setHeaderData(3, Qt::Horizontal, "Номер телефону");
    modelData->setHeaderData(4, Qt::Horizontal, "Адреса");
    modelData->setHeaderData(5, Qt::Horizontal, "Стать");
    modelData->setHeaderData(6, Qt::Horizontal, "День народження");
}

void EmployeesModel::addToRomove(const int& row)
{
    int idProduct = modelData->index(row, 0).data().toInt();

    if(!listToRemove.contains(idProduct))
        listToRemove.append(idProduct);
    else
        listToRemove.removeOne(idProduct);
}

