#ifndef EMPLOYEESMODEL_H
#define EMPLOYEESMODEL_H

#include "basemodel.h"

class EmployeesModel : public BaseModel
{
public:
    EmployeesModel(ConnectionHandler* connection);
    void addToRomove(const int& row);
    QList<int>& getListToRemove() { return listToRemove; }

private:
    void setHeaderModel() override;

private:
    QList<int> listToRemove;
};

#endif // EMPLOYEESMODEL_H
