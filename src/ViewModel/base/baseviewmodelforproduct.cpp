#include "baseviewmodelforproduct.h"

BaseViewModelForProduct::BaseViewModelForProduct(ProductModel* productModel, QString standartRequest)
    : BaseViewModel(standartRequest), productModel(productModel)
{
    filter = new Filter;
}

void BaseViewModelForProduct::priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo)
{
    productModel->updateModel(standartRequest + filter->priceFilterChangedSlots(inputTo, inputDo));
    emit clearLableSignal();
}

void BaseViewModelForProduct::checkBoxEnabledSlots(const int& state)
{
    productModel->updateModel(standartRequest + filter->checkBoxEnabled(state, sender()));
    emit clearLableSignal();
}

void BaseViewModelForProduct::selectedElemTableViewSlots(const QModelIndex& i)
{
    emit clearLableSignal();
    QHash<QLabel*, QLineEdit*>* list = productModel->createElementForDispleyCharact("call getCharacteristicForProduct('" +
                                                                                   i.model()->data(i.model()->index(i.row(), 0)).toString() +"')");

    if(!list)
        return;

    emit clearLableSignal();
    for (QLineEdit*& value : (*list))
        emit addInfoProductSignal(list->key(value), value);

    emit addInfoProductSignal();

    delete list;
}

BaseViewModelForProduct::~BaseViewModelForProduct()
{
    delete filter;
}
