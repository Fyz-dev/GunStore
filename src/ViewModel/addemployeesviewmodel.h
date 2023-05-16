#ifndef ADDEMPLOYEESVIEWMODEL_H
#define ADDEMPLOYEESVIEWMODEL_H

#include "baseviewmodel.h"
#include "employeesmodel.h"

class AddEmployeesViewModel : public QObject, public BaseViewModel
{
    Q_OBJECT

public:
    AddEmployeesViewModel(EmployeesModel* employeesModel);
    ~AddEmployeesViewModel();
    void update() override;
    void applyChanges(const QString& FIO, const QString& password, const QString& position, const QString& phoneNumber, const QString& address, const QString& gender, const QString& date);

    bool isEmployees(const QString& text);

signals:
    void addItemsToComboBox(const QStringList& first, const QStringList& second);
    void close();

private:
    EmployeesModel* employeesModel;
};

#endif // ADDEMPLOYEESVIEWMODEL_H
