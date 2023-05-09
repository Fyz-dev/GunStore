#ifndef EMPLOYEESMODEL_H
#define EMPLOYEESMODEL_H

#include "basemodel.h"
#include "elementpeople.h"

class EmployeesModel : public BaseModel
{
public:
    EmployeesModel(ConnectionHandler* connection);
    void addToRomove(const int& row);
    QList<ElementPeople*>& updateInfoBuyPeople(QWidget* parent, const QString& isDelete = "0");
    const QString& getIdWorker() { return connection->getIdWorker(); }

private:
    void setHeaderModel() override;

private:
    QList<ElementPeople*> list;
};

#endif // EMPLOYEESMODEL_H
