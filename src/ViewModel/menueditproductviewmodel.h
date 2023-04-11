#ifndef MENUEDITPRODUCTVIEWMODEL_H
#define MENUEDITPRODUCTVIEWMODEL_H

#include "baseviewmodelforproduct.h"
#include "productmodel.h"

class MenuEditProductViewModel : public BaseViewModelForProduct
{
public:
    MenuEditProductViewModel(ProductModel* productModel);
    void update() override;

};

#endif // MENUEDITPRODUCTVIEWMODEL_H
