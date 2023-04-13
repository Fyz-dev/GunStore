#include "mainmenuviewmodel.h"

MainMenuViewModel::MainMenuViewModel(ProductModel* productModel) : BaseViewModelForProduct(productModel)
{}

void MainMenuViewModel::update()
{
    if(!productModel->updateModel("product", "", 8, QSqlRelation("category", "id_category", "c_name")))
        return;

    emit modelChangedSignal(productModel->getModelData());

    productModel->updateListFilter();
    emit clearCheckBoxSignal();

    addCheckBox(productModel->createCheckBox(productModel->getListCategory()), LayoutState::CATEGORY);
    addCheckBox(productModel->createCheckBox(productModel->getListCountry()), LayoutState::COUNTRY);
    addCheckBox(productModel->createCheckBox(productModel->getListBrand()), LayoutState::BRAND);
}

void MainMenuViewModel::addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName)
{
    for (QCheckBox* checkBox : listCheckBox) {
        connect(checkBox, &QCheckBox::stateChanged, this, &MainMenuViewModel::checkBoxEnabledSlots);
        emit addCheckBoxSignal(checkBox, layoutName);
    }
}
