#include "addproductdialogviewmodel.h"

AddProductDialogViewModel::AddProductDialogViewModel(ProductModel* productModel) :
    BaseViewModel(),
    productModel(productModel)
{}

void AddProductDialogViewModel::update()
{
    QList<QString> list;
    productModel->updateList(list, "select c_name from product join category using(id_category) group by id_category");

    createCheckBox(list);
}

void AddProductDialogViewModel::createCheckBox(const QList<QString>& list)
{
    for (const QString& text : list)
        emit updateComboBoxSignals(text);
}

void AddProductDialogViewModel::selectedItemComboBox(const int& i, const QComboBox* comboBoxSender)
{
    if(i == -1)
        return;

    QList<QString> list;
    productModel->updateList(list, "call getCharacteristicForCategory('" + comboBoxSender->itemText(i) + "')");

    QComboBox* comboBox = new QComboBox;
    comboBox->addItems(list);

    emit setComboBoxSignals(comboBox);
}

void AddProductDialogViewModel::addNewProduct(const QString& name, const QString& price, const QString& brand, const QString& weight, const QString& package, const QString& country, const QString& category, const QTableWidget* table)
{
    productModel->requestBD("INSERT INTO product(p_name, p_priceOne, p_brand, p_weight, p_package, p_country, id_category) VALUES('" +
    name + "'," + price + ",'" + brand + "'," + weight + ",'" + package + "','" + country + "', (select id_category from category where c_name = '" + category + "'))");

    const int lastId = productModel->getLastInsertId();

    for (int i = 0; i < table->rowCount() - 1; ++i)
    {
        productModel->requestBD("INSERT INTO productvalue(id_product, id_categoryCharacteristic, value) VALUES(" +
        QString::number(lastId) + ", (select id_categoryCharacteristic from categorycharacteristic where id_category = (select id_category from category where c_name = '" +
        category + "') and id_characteristic = (select id_characteristic from characteristic where charact_name = '" + table->item(i, 0)->text() + "')), '" + table->item(i, 1)->text() + "')");
    }
}

AddProductDialogViewModel::~AddProductDialogViewModel()
{
    delete productModel;
}
