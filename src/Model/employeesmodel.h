#ifndef EMPLOYEESMODEL_H
#define EMPLOYEESMODEL_H

#include "basemodel.h"

class EmployeesModel : public BaseModel
{
public:
    EmployeesModel(ConnectionHandler* connection);
    void addToRomove(const int& row);

private:
    void setHeaderModel() override;
};

#endif // EMPLOYEESMODEL_H
