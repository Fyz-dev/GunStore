#ifndef MENUEDITPRODUCTVIEWMODEL_H
#define MENUEDITPRODUCTVIEWMODEL_H

#include "baseviewmodelforproduct.h"
#include "productmodel.h"
#include "delegatefortableview.h"

class MenuEditProductViewModel : public BaseViewModelForProduct
{
    Q_OBJECT

public:
    MenuEditProductViewModel(ProductModel* productModel);
    ~MenuEditProductViewModel();

public:
    void update() override;
    void addItemToRemove(const int& row);
    const QList<int>& getListToRemove() { return listToRemove; };
    DelegateForTableView* getDelegate() { return delegate; };
    void applyChanges();

signals:
    void showMessageBoxSignals();

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) override;

private:
    QList<int> listToRemove;
    DelegateForTableView* delegate;
};

#endif // MENUEDITPRODUCTVIEWMODEL_H
