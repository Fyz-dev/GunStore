#ifndef MENUEMPLOYEES_H
#define MENUEMPLOYEES_H

#include "employeesmodel.h"
#include "iview.h"

#include <QWidget>

namespace Ui {
class MenuEmployees;
}

class MenuEmployees : public QWidget, public IView
{
    Q_OBJECT

public:
    explicit MenuEmployees(EmployeesModel* employeesModel, QWidget *parent = nullptr);
    ~MenuEmployees();

    void show() override;
    void hide() override;

signals:
    void openAddNewEmployees();

private:
    void update();

private:
    Ui::MenuEmployees *ui;
    EmployeesModel* employeesModel;
};

#endif // MENUEMPLOYEES_H
