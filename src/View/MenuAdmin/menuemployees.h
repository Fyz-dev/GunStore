#ifndef MENUEMPLOYEES_H
#define MENUEMPLOYEES_H

#include "menuemployeesviewmodel.h"

#include <QWidget>

namespace Ui {
class MenuEmployees;
}

class MenuEmployees : public QWidget
{
    Q_OBJECT

public:
    explicit MenuEmployees(MenuEmployeesViewModel* menuEmployeesViewModel, QWidget *parent = nullptr);
    ~MenuEmployees();

public slots:
    void modelChangedSlots(QAbstractTableModel * modelData);

private slots:
    void buttonAddEmployees_clicked();

signals:
    void openAddNewEmployees();

private:
    void connected();

private:
    Ui::MenuEmployees *ui;
    MenuEmployeesViewModel* menuEmployeesViewModel;
};

#endif // MENUEMPLOYEES_H
