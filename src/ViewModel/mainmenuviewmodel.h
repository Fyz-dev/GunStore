#ifndef MAINMENUVIEWMODEL_H
#define MAINMENUVIEWMODEL_H

#include "productmodel.h"
#include "LayoutState.h"
#include "baseviewmodelforproduct.h"
#include "delegatefortableview.h"

class MainMenuViewModel : public BaseViewModelForProduct
{
public:
    MainMenuViewModel(ProductModel* productModel);
    ~MainMenuViewModel();
    void update() override;
    void changedListProductForSale(const int& row, const int& count);
    DelegateForTableView* getDelegate() { return delegate; };

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) override;
    QList<int> listProductForSale;
    QHash<int, int> listProductCount;
    DelegateForTableView* delegate;
};

#endif // MAINMENUVIEWMODEL_H
