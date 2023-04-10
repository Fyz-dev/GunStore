#ifndef MENUEDITPRODUCTVIEWMODEL_H
#define MENUEDITPRODUCTVIEWMODEL_H

#include "baseviewmodel.h"
#include "productmodel.h"

class MenuEditProductViewModel : public BaseViewModel
{
public:
    MenuEditProductViewModel(ProductModel* productModel);
    void update() override;

private:
    ProductModel* productModel;
};

#endif // MENUEDITPRODUCTVIEWMODEL_H
