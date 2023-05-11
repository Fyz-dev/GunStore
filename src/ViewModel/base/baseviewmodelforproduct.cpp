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
    productModel->updateModel("product", QString("p_name LIKE '%%1%' and isDelete = %2 and ").arg(textSearch, isDelete) + filter->priceFilterChangedSlots(inputTo, inputDo), 8, QSqlRelation("category", "id_category", "c_name"));
    emit clearLableSignal();
}

void BaseViewModelForProduct::checkBoxEnabledSlots(const int& state, QObject* sender, const QString& isDelete)
{  
    productModel->updateModel("product", QString("p_name LIKE '%%1%' and isDelete = %2 and ").arg(textSearch, isDelete) + filter->checkBoxEnabled(state, sender), 8, QSqlRelation("category", "id_category", "c_name"));
    emit clearLableSignal();
}

void BaseViewModelForProduct::selectedElemTableViewSlots(const QModelIndex& i, bool lineEditIsReadOnly)
{
    emit clearLableSignal();
    productModel->createElementForDispleyCharact("call getCharacteristicForProduct(" +
    i.model()->data(i.model()->index(i.row(), 0)).toString() +")", lineEditIsReadOnly);

    emit addInfoProductSignal();
}

void BaseViewModelForProduct::updateWithSearch(const QString& text, const QString& isDelete)
{
    textSearch = text;
    productModel->updateModel("product", QString("p_name LIKE '%%1%' and isDelete = %2 and ").arg(textSearch, isDelete) + filter->checkBoxEnabled(-1, nullptr), 8, QSqlRelation("category", "id_category", "c_name"));
    emit clearLableSignal();
}

BaseViewModelForProduct::~BaseViewModelForProduct()
{
    delete filter;
}
