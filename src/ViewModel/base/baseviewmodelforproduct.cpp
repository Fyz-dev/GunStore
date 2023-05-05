#include "baseviewmodelforproduct.h"

BaseViewModelForProduct::BaseViewModelForProduct(ProductModel* productModel, QString standartRequest)
    : BaseViewModel(standartRequest), productModel(productModel)
{
    connect(productModel, &ProductModel::addInfoProductSignal, this, [&](QWidget* widget)
    {
       emit addInfoProductSignal(widget);
    });
}

void BaseViewModelForProduct::priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo, const QString& isDelete)
{
    productModel->updateModel("product", QString("isDelete = %1 and ").arg(isDelete) + filter->priceFilterChangedSlots(inputTo, inputDo), 8, QSqlRelation("category", "id_category", "c_name"));
    emit clearLableSignal();
}

void BaseViewModelForProduct::checkBoxEnabledSlots(const int& state, QObject* sender, const QString& isDelete)
{
    productModel->updateModel("product", QString("isDelete = %1 and ").arg(isDelete) + filter->checkBoxEnabled(state, sender), 8, QSqlRelation("category", "id_category", "c_name"));
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
