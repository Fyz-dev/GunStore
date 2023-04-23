#ifndef MENUEMPLOYEESVIEWMODEL_H
#define MENUEMPLOYEESVIEWMODEL_H

#include "baseviewmodel.h"
#include "employeesmodel.h"
#include "delegatefortableviewworker.h"

class MenuEmployeesViewModel : public QObject, public BaseViewModel
{
    Q_OBJECT

public:
    MenuEmployeesViewModel(EmployeesModel* employeesModel);
    ~MenuEmployeesViewModel();

public:
    void update() override;
    void addToRemove(const int& row);
    void applyChanges();
    DelegateForTableViewWorker* getDelegate() { return delegate; }

signals:
    void modelChangedSignals(QAbstractTableModel* modelData);

private:
    EmployeesModel* employeesModel;
    DelegateForTableViewWorker* delegate;
};

#endif // MENUEMPLOYEESVIEWMODEL_H
