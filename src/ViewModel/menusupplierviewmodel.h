#ifndef MENUSUPPLIERVIEWMODEL_H
#define MENUSUPPLIERVIEWMODEL_H

#include "baseviewmodel.h"
#include "suppliermodel.h"
#include "delegatefortableview.h"

class MenuSupplierViewModel : public QObject, public BaseViewModel
{
    Q_OBJECT

public:
    MenuSupplierViewModel(SupplierModel* supplierModel);
    ~MenuSupplierViewModel();
    void update() override;
    void applyChanges();
    void addToRemove(const int& row);
    DelegateForTableView* getDelegate() { return delegate; }

signals:
    void modelChangedSignals(QAbstractItemModel* model);

private:
    SupplierModel* supplierModel;
    DelegateForTableView* delegate;
};

#endif // MENUSUPPLIERVIEWMODEL_H
