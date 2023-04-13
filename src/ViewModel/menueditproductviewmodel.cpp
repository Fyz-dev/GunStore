#include "menueditproductviewmodel.h"
#include <QSqlError>

MenuEditProductViewModel::MenuEditProductViewModel(ProductModel* productModel) : BaseViewModelForProduct(productModel)
{}

void MenuEditProductViewModel::update()
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

void MenuEditProductViewModel::addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName)
{
    for (QCheckBox* checkBox : listCheckBox) {
        connect(checkBox, &QCheckBox::stateChanged, this, &MenuEditProductViewModel::checkBoxEnabledSlots);
        emit addCheckBoxSignal(checkBox, layoutName);
    }
}

void MenuEditProductViewModel::applyChanges()
{
    productModel->getModelData()->submitAll();
    qDebug() << productModel->getModelData()->lastError();
}
