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
    void update(const QString& isDelete, bool isUpdateModel = true);
    void addItemToRemove(const int& row);
    void addItemToReturn(const int& row);
    void insertCharactToBD(const QString& idProduct, const QString& charact, const QString& value);
    void updateChange();

    void applyChanges();
    bool isChanged();

    //GET & SET
    QList<int>& getListToRemove() { return listToRemove; };
    QList<int>& getListToReturn() { return listToReturn; };
    DelegateForTableView* getDelegate() { return delegate; };
    ProductModel* getProductModel() { return productModel; }
    QList<QString>  getListCharact(const QModelIndex& i);
    void setProductModel(ProductModel* productModel) { this->productModel = productModel; }

signals:
    void showMessageBoxSignals();

private slots:
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QList<int>& roles);

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) override;
    void update() override;

private:
    QList<int> listToRemove;
    QList<int> listToReturn;
    std::unordered_map<int, std::unordered_map<int, QString>> tableListChange;
    DelegateForTableViewProduct* delegate;
};

#endif // MENUEDITPRODUCTVIEWMODEL_H
