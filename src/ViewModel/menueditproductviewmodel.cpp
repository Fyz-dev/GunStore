#include "menueditproductviewmodel.h"

MenuEditProductViewModel::MenuEditProductViewModel(ProductModel* productModel) : BaseViewModelForProduct(productModel)
{
    delegate = new DelegateForTableViewProduct(listToRemove, productModel->getModelData(), QColor(255, 0, 13, 80));
}

void MenuEditProductViewModel::update(const QString& isDelete)
{
    if(!productModel->updateModel("product", QString("isDelete = %1").arg(isDelete), 8, QSqlRelation("category", "id_category", "c_name")))
        return;

    emit modelChangedSignal(productModel->getModelData());

    if(filter)
        delete filter;
    filter = new Filter;

    productModel->updateListFilter(isDelete);
    emit clearCheckBoxSignal();

    addCheckBox(productModel->createCheckBox(productModel->getListCategory()), LayoutState::CATEGORY);
    addCheckBox(productModel->createCheckBox(productModel->getListCountry()), LayoutState::COUNTRY);
    addCheckBox(productModel->createCheckBox(productModel->getListBrand()), LayoutState::BRAND);
}

void MenuEditProductViewModel::update(){}

void MenuEditProductViewModel::addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName)
{
    for (QCheckBox* checkBox : listCheckBox)
        emit addCheckBoxSignal(checkBox, layoutName);
}

void MenuEditProductViewModel::applyChanges()
{
    if(!productModel->getModelData()->isDirty() && productModel->getListChangedCharacteristic().isEmpty() && listToRemove.isEmpty() && listToReturn.isEmpty())
        return;

    //Обновляем информацию в БД
    for(QHash<int, QString>::const_iterator i = productModel->getListChangedCharacteristic().constBegin(); i != productModel->getListChangedCharacteristic().constEnd(); ++i)
    {
        productModel->requestBD("UPDATE productvalue SET value = '" + i.value()
                                        + "' WHERE id_productValue = " + QString::number(i.key()));
    }

    if(productModel->getModelData()->isDirty())
        productModel->getModelData()->submitAll();

    //Удаляем информацию в БД
    for (int id : listToRemove)
        productModel->requestBD("UPDATE product SET isDelete = 1 where id_product = " + QString::number(id));

    for (int id : listToReturn)
        productModel->requestBD("UPDATE product SET isDelete = 0 where id_product = " + QString::number(id));

    emit showMessageBoxSignals();
    productModel->getListChangedCharacteristic().clear();
    listToRemove.clear();
}

void MenuEditProductViewModel::addItemToRemove(const int& row)
{
    int idProduct = productModel->getModelData()->index(row, 0).data().toInt();

    if(!listToRemove.contains(idProduct))
        listToRemove.append(idProduct);
    else
        listToRemove.removeOne(idProduct);
}

void MenuEditProductViewModel::addItemToReturn(const int& row)
{
    int idProduct = productModel->getModelData()->index(row, 0).data().toInt();

    if(!listToReturn.contains(idProduct))
        listToReturn.append(idProduct);
    else
        listToReturn.removeOne(idProduct);
}

MenuEditProductViewModel::~MenuEditProductViewModel()
{
    delete delegate;
}
