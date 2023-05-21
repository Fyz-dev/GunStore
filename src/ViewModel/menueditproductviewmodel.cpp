#include "menueditproductviewmodel.h"

MenuEditProductViewModel::MenuEditProductViewModel(ProductModel* productModel) : BaseViewModelForProduct(productModel),
    delegate(new DelegateForTableViewProduct(listToRemove, productModel->getModelData(), QColor(255, 0, 13, 80)))
{}

void MenuEditProductViewModel::update(const QString& isDelete, bool isUpdateModel)
{
    productModel->getListChangedCharacteristic().clear();
    listToRemove.clear();
    listToReturn.clear();

    if(isUpdateModel)
        if(!productModel->updateModel("product", QString("isDelete = %1").arg(isDelete), 8, QSqlRelation("category", "id_category", "c_name")))
            return;

    emit modelChangedSignal(productModel->getModelData());

    connect(productModel->getModelData(), &QSqlRelationalTableModel::dataChanged, this, &MenuEditProductViewModel::dataChanged);

    if(filter)
        delete filter;
    filter = new Filter;

    productModel->updateListFilter(isDelete);
    emit clearCheckBoxSignal();

    addCheckBox(productModel->createCheckBox(productModel->getListCategory()), LayoutState::CATEGORY);
    addCheckBox(productModel->createCheckBox(productModel->getListCountry()), LayoutState::COUNTRY);
    addCheckBox(productModel->createCheckBox(productModel->getListBrand()), LayoutState::BRAND);
}

void MenuEditProductViewModel::update()
{}

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
    listToReturn.clear();
    tableListChange.clear();
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

void MenuEditProductViewModel::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QList<int>& roles)
{
    QSqlRelationalTableModel* model = productModel->getModelData();
    int firstKey = model->index(topLeft.row(), 0).data().toInt();
    int secondKey = topLeft.column();

//    auto outerIt = tableListChange.find(firstKey);
//    if(outerIt != tableListChange.end())
//    tableListChange.emplace(firstKey, std::unordered_map<int, QString>{{secondKey, model->index(topLeft.row(), topLeft.column()).data().toString()}});

    tableListChange[firstKey][secondKey] = model->index(topLeft.row(), topLeft.column()).data().toString();
}

bool MenuEditProductViewModel::isChanged()
{
    if(!productModel->getModelData()->isDirty() && productModel->getListChangedCharacteristic().isEmpty() && listToRemove.isEmpty() && listToReturn.isEmpty())
        return false;

    return true;
}

QList<QString> MenuEditProductViewModel::getListCharact(const QModelIndex& i)
{
    QList<QString> list;
    productModel->updateList(list, QString("select charact_name from categorycharacteristic join characteristic using(id_characteristic) where id_categoryCharacteristic not in(select id_categoryCharacteristic from productvalue where id_product = %1) and id_category = (select id_category from product where id_product = %1)").arg(i.model()->index(i.row(), 0).data().toString()));
    return list;
}

void MenuEditProductViewModel::insertCharactToBD(const QString& idProduct, const QString& charact, const QString& value)
{
    productModel->requestBD(QString("INSERT INTO productvalue(id_product, id_categoryCharacteristic, `value`) VALUES(%1, (select id_categoryCharacteristic from categorycharacteristic join characteristic using(id_characteristic) where charact_name = '%2' and id_category = (select id_category from product where id_product = %1)), '%3')").arg(idProduct, charact, value));
}

void MenuEditProductViewModel::updateChange()
{
    QSqlRelationalTableModel* model = productModel->getModelData();
    for (int i = 0; i < model->rowCount(); ++i)
        if(tableListChange.find(model->index(i, 0).data().toInt()) != tableListChange.end())
            for (auto it = tableListChange[model->index(i, 0).data().toInt()].begin(); it != tableListChange[model->index(i, 0).data().toInt()].end(); ++it)
                model->setData(QModelIndex(model->index(i, it->first)), it->second);
}

MenuEditProductViewModel::~MenuEditProductViewModel()
{
    delete delegate;
}
