#include "mainmenuviewmodel.h"

MainMenuViewModel::MainMenuViewModel(ProductModel* productModel) : BaseViewModelForProduct(productModel)
{
    delegate = new DelegateForTableView(listProductForSale, productModel->getModelData(), QColor(2, 204, 136, 80));
}

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

void MainMenuViewModel::changedListProductForSale(const int& row, const int& count)
{
    if(row == -1)
        return;

    int idProduct = productModel->getModelData()->index(row, 0).data().toInt();

    if(!listProductForSale.contains(idProduct))
    {
        listProductForSale.append(idProduct);
        listProductCount[idProduct] = count;
    }
    else
    {
        listProductForSale.removeOne(idProduct);
        listProductCount.remove(idProduct);
    }
}

MainMenuViewModel::~MainMenuViewModel()
{
    delete delegate;
}
