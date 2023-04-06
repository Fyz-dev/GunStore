#include "mainmenuviewmodel.h"

MainMenuViewModel::MainMenuViewModel(ProductModel* productModel) : BaseViewModel("select p_name as 'Назва', p_priceOne as 'Ціна(грн.)', p_count as 'Кількість(шт.)', p_brand as 'Бренд', p_weight as 'Вес(г.)',p_package as 'Упаковка', p_country as 'Країна', c_name as 'Категорія' from product join category using(id_category)")
    , productModel(productModel)
{}

void MainMenuViewModel::update()
{
    if(!productModel->updateModel(standartRequest))
        return;

    emit modelChangedSignal(productModel->getModelData());
    productModel->updateListFilter();

    listCheckBoxEnabled.clear();
    emit clearCheckBoxSignal();

    createCheckBox(productModel->getListCategory(), LayoutState::CATEGORY);
    createCheckBox(productModel->getListCountry(), LayoutState::COUNTRY);
    createCheckBox(productModel->getListBrand(), LayoutState::BRAND);
}

void MainMenuViewModel::checkBoxEnabledSlots(const int& state)
{
    if(state == 0)
    {
        int i = listCheckBoxEnabled.indexOf(sender());
        if(i != -1)
            listCheckBoxEnabled.removeAt(i);
    }

    if(state == 2)
        listCheckBoxEnabled.append(sender());

    updateModelByFilter();
}

void MainMenuViewModel::priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo)
{
    static const QRegularExpression regex("^[0-9]+$");

    if(inputTo->text().length() != 0 && !regex.match(inputTo->text()).hasMatch())
        return inputTo->setText("");


    if(inputDo->text().length() != 0 && !regex.match(inputDo->text()).hasMatch())
        return inputDo->setText("");

    priceTo = inputTo->text(), priceDo = inputDo->text();
    updateModelByFilter();
}

void MainMenuViewModel::updateModelByFilter()
{
    QString filterCategory, filterCountry, filterBrand, filterPrice;

    filterPrice = " p_priceOne >= " + (priceTo != "" ? priceTo : "0");
    filterPrice += priceDo == "" ? "" : " and p_priceOne <= " + priceDo;

    foreach(QObject* value, listCheckBoxEnabled)
    {
        if(value->parent()->objectName() == "frameCategorys")
            filterCategory += "'" + qobject_cast<QCheckBox*>(value)->text() + "',";

        if(value->parent()->objectName() == "frameCountries")
            filterCountry += "'" + qobject_cast<QCheckBox*>(value)->text() + "',";

        if(value->parent()->objectName() == "frameBrands")
            filterBrand += "'" + qobject_cast<QCheckBox*>(value)->text() + "',";
    }

    filterCategory = filterCategory == "" ? "c_name" : filterCategory.chopped(1);
    filterCountry = filterCountry == "" ? "p_country" : filterCountry.chopped(1);
    filterBrand = filterBrand == "" ? "p_brand" : filterBrand.chopped(1);

    emit clearLableSignal();
    productModel->updateModel(standartRequest + "where 1=1 " + "and c_name in(" + filterCategory + ") and p_country in(" +
                              filterCountry + ") and p_brand in(" + filterBrand + ") and (" + filterPrice + ")");
}

void MainMenuViewModel::selectedElemTableViewSlots(const QModelIndex& i)
{
    QHash<QString, QString> list;
    emit clearLableSignal();
    productModel->updateListForCharacteristic(list, "call getCharacteristicForProduct('" + i.model()->data(i.model()->index(i.row(), 0)).toString() +"')");
    createLable(list);
}

void MainMenuViewModel::createCheckBox(const QList<QString>& list, LayoutState layoutName)
{
    for(const QString& value : list)
    {
        QCheckBox* checkBox = new QCheckBox;
        checkBox->setText(value);
        checkBox->setToolTip(value);
        connect(checkBox, &QCheckBox::stateChanged, this, &MainMenuViewModel::checkBoxEnabledSlots);
        emit addCheckBoxSignal(checkBox, layoutName);
    }
}

void MainMenuViewModel::createLable(const QHash<QString, QString>& list)
{
    for(const QString& value : list)
    {
        QLabel* label = new QLabel;
        label->setText(list.key(value) + ":");
        label->setAlignment(Qt::AlignLeft);

        QLineEdit* lineEdit = new QLineEdit;
        lineEdit->setText(value);
        lineEdit->setReadOnly(true);

        emit addInfoProductSignal(label, lineEdit);
    }
    emit addInfoProductSignal();
}
