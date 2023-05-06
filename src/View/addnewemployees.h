#ifndef ADDNEWEMPLOYEES_H
#define ADDNEWEMPLOYEES_H

#include "addemployeesviewmodel.h"
#include "centerednotification.h"
#include "iview.h"

#include <QDialog>

namespace Ui {
class AddNewEmployees;
}

class AddNewEmployees : public QDialog, public IView
{
    Q_OBJECT

public:
    explicit AddNewEmployees(AddEmployeesViewModel* addEmployeesViewModel, QWidget *parent = nullptr);
    ~AddNewEmployees();

public slots:
    void addItemsToComboBox(const QStringList& first, const QStringList& second);
    void close();

    void show() override;
    void hide() override;

private:
    void connected();

private:
    Ui::AddNewEmployees *ui;
    AddEmployeesViewModel* addEmployeesViewModel;
    CenteredNotification* notification;
    static const QRegularExpression regexNumberPhone;
    static const QRegularExpression regexNull;
};

#endif // ADDNEWEMPLOYEES_H
