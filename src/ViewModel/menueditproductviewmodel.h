#ifndef MENUEDITPRODUCTVIEWMODEL_H
#define MENUEDITPRODUCTVIEWMODEL_H

#include "baseviewmodelforproduct.h"
#include "productmodel.h"
#include "delegatefortableviewproduct.h"

class MenuEditProductViewModel : public BaseViewModelForProduct
{
    Q_OBJECT

public:
    MenuEditProductViewModel(ProductModel* productModel);
    ~MenuEditProductViewModel();

public:
    void update(const QString& isDelete);
    void addItemToRemove(const int& row);
    void addItemToReturn(const int& row);
    QList<int>& getListToRemove() { return listToRemove; };
    QList<int>& getListToReturn() { return listToReturn; };
    DelegateForTableView* getDelegate() { return delegate; };
    void applyChanges();

signals:
    void showMessageBoxSignals();

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) override;
    void update() override;

private:
    QList<int> listToRemove;
    QList<int> listToReturn;
    DelegateForTableViewProduct* delegate;
};

#endif // MENUEDITPRODUCTVIEWMODEL_H
