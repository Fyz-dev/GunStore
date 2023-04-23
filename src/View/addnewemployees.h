#ifndef ADDNEWEMPLOYEES_H
#define ADDNEWEMPLOYEES_H

#include <QDialog>
#include "addemployeesviewmodel.h"

namespace Ui {
class AddNewEmployees;
}

class AddNewEmployees : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewEmployees(AddEmployeesViewModel* addEmployeesViewModel, QWidget *parent = nullptr);
    ~AddNewEmployees();

public slots:
    void addItemsToComboBox(const QStringList& first, const QStringList& second);
    void close();

private:
    void connected();

private:
    Ui::AddNewEmployees *ui;
    AddEmployeesViewModel* addEmployeesViewModel;
};

#endif // ADDNEWEMPLOYEES_H
