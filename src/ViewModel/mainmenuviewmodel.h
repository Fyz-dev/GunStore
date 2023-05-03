#ifndef MAINMENUVIEWMODEL_H
#define MAINMENUVIEWMODEL_H

#include "productmodel.h"
#include "LayoutState.h"
#include "baseviewmodelforproduct.h"
#include "delegatefortableview.h"

class MainMenuViewModel : public BaseViewModelForProduct
{
    Q_OBJECT

public:
    MainMenuViewModel(ProductModel* productModel);
    ~MainMenuViewModel();
    void update() override;
    bool changedListProductForSale(const int& row, const int& count, QLineEdit* lineEdit);
    void syncHashAndList();
    //Get
    DelegateForTableView* getDelegate() { return delegate; };
    const QList<int>& getListProductForSale() { return listProductForSale; }
    QHash<int, int>& getListProduct() { return listProduct; }

signals:
    void messageShow(const QString& message);

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) override;
    QList<int> listProductForSale;
    QHash<int, int> listProduct;
    DelegateForTableView* delegate;
};

#endif // MAINMENUVIEWMODEL_H
