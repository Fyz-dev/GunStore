#ifndef MENUEMPLOYEES_H
#define MENUEMPLOYEES_H

#include "employeesmodel.h"

#include <QWidget>

namespace Ui {
class MenuEmployees;
}

class MenuEmployees : public QWidget
{
    Q_OBJECT

public:
    explicit MenuEmployees(EmployeesModel* employeesModel, QWidget *parent = nullptr);
    ~MenuEmployees();

signals:
    void openAddNewEmployees();

private:
    void update();

private:
    Ui::MenuEmployees *ui;
    EmployeesModel* employeesModel;
};

#endif // MENUEMPLOYEES_H
