#include "baseviewmodelforproduct.h"

BaseViewModelForProduct::BaseViewModelForProduct(ProductModel* productModel, QString standartRequest)
    : BaseViewModel(standartRequest), productModel(productModel)
{
    filter = new Filter;

    connect(productModel, &ProductModel::addInfoProductSignal, this, [&](QWidget* widget)
    {
       emit addInfoProductSignal(widget);
    });
}

void BaseViewModelForProduct::priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo)
{
    productModel->updateModel("product", filter->priceFilterChangedSlots(inputTo, inputDo), 8, QSqlRelation("category", "id_category", "c_name"));
    emit clearLableSignal();
}

void BaseViewModelForProduct::checkBoxEnabledSlots(const int& state)
{
    productModel->updateModel("product", filter->checkBoxEnabled(state, sender()), 8, QSqlRelation("category", "id_category", "c_name"));
    emit clearLableSignal();
}

void BaseViewModelForProduct::selectedElemTableViewSlots(const QModelIndex& i, bool lineEditIsReadOnly)
{
    emit clearLableSignal();
    productModel->createElementForDispleyCharact("call getCharacteristicForProduct(" +
    i.model()->data(i.model()->index(i.row(), 0)).toString() +")", lineEditIsReadOnly);

    emit addInfoProductSignal();
}

BaseViewModelForProduct::~BaseViewModelForProduct()
{
    delete filter;
}
