#ifndef EMPLOYEESMODEL_H
#define EMPLOYEESMODEL_H

#include "basemodel.h"

class EmployeesModel : public BaseModel
{
public:
    EmployeesModel(QSqlDatabase* db);
    void addToRomove(const int& row);
    const QList<int>& getListToRemove() { return listToRemove; }

private:
    void setHeaderModel() override;

private:
    QList<int> listToRemove;
};

#endif // EMPLOYEESMODEL_H
