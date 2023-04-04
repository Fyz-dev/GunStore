#include "mainmenuviewmodel.h"

MainMenuViewModel::MainMenuViewModel(ProductModel* productModel) :
    productModel(productModel),
    standartRequest("select p_name as 'Назва', p_priceOne as 'Ціна(грн.)', p_count as 'Кількість(шт.)', p_brand as 'Бренд', p_weight as 'Вес(г.)',p_package as 'Упаковка', p_country as 'Країна', c_name as 'Категорія' from product join category using(id_category)")
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

void MainMenuViewModel::checkBoxEnabledSlots(int state)
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

void MainMenuViewModel::updateModelByFilter()
{
    QString filterCategory, filterCountry, filterBrand;
    foreach(QObject* value, listCheckBoxEnabled)
    {
        if(value->parent()->objectName() == "frameCategorys")
        {
            if(filterCategory != "")
                filterCategory += " or ";
            filterCategory += " c_name = '" + qobject_cast<QCheckBox*>(value)->text() + "'";
        }

        if(value->parent()->objectName() == "frameCountries")
        {
            if(filterCountry != "")
                filterCountry += " or ";
            filterCountry += " p_country = '" + qobject_cast<QCheckBox*>(value)->text() + "'";
        }

        if(value->parent()->objectName() == "frameBrands")
        {
            if(filterBrand != "")
                filterBrand += " or ";
            filterBrand += " p_brand = '" + qobject_cast<QCheckBox*>(value)->text() + "'";
        }
    }

    QString filter;
    filter += filterCategory != "" ?  " and (" + filterCategory + ")" : "";
    filter += filterCountry != "" ?  " and (" + filterCountry + ")" : "";
    filter += filterBrand != "" ?  " and (" + filterBrand + ")" : "";

    productModel->updateModel(standartRequest + "where 1=1 " + filter);
}

void MainMenuViewModel::createCheckBox(QList<QString> list, LayoutState layoutName)
{
    foreach (auto value, list)
    {
        QCheckBox* checkBox = new QCheckBox;
        checkBox->setText(value);
        checkBox->setToolTip(value);
        connect(checkBox, &QCheckBox::stateChanged, this, &MainMenuViewModel::checkBoxEnabledSlots);
        emit addCheckBoxSignal(checkBox, layoutName);
    }
}
