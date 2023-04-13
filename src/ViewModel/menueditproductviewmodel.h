#ifndef MENUEDITPRODUCTVIEWMODEL_H
#define MENUEDITPRODUCTVIEWMODEL_H

#include "baseviewmodelforproduct.h"
#include "productmodel.h"

class MenuEditProductViewModel : public BaseViewModelForProduct
{
    Q_OBJECT

public:
    MenuEditProductViewModel(ProductModel* productModel);
    void update() override;

public slots:
    void applyChanges();

signals:
    void showMessageBoxSignals();

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) override;

};

#endif // MENUEDITPRODUCTVIEWMODEL_H
