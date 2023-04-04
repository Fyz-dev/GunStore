#ifndef ADDNEWEMPLOYEES_H
#define ADDNEWEMPLOYEES_H

#include <QDialog>

namespace Ui {
class AddNewEmployees;
}

class AddNewEmployees : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewEmployees(QWidget *parent = nullptr);
    ~AddNewEmployees();

private:
    Ui::AddNewEmployees *ui;
};

#endif // ADDNEWEMPLOYEES_H
