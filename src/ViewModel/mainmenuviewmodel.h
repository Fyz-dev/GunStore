#ifndef MAINMENUVIEWMODEL_H
#define MAINMENUVIEWMODEL_H

#include "productmodel.h"
#include "LayoutState.h"
#include "baseviewmodelforproduct.h"

class MainMenuViewModel : public BaseViewModelForProduct
{
public:
    MainMenuViewModel(ProductModel* productModel);
    void update() override;

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName);
};

#endif // MAINMENUVIEWMODEL_H
