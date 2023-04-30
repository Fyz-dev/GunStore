#include "filter.h"

Filter::Filter()
{

}

QString Filter::checkBoxEnabled(const int& state, QObject* checkBox)
{
    if(state == 0)
    {
        int i = listCheckBoxEnabled.indexOf(checkBox);
        if(i != -1)
            listCheckBoxEnabled.removeAt(i);
    }

    if(state == 2)
        listCheckBoxEnabled.append(checkBox);

    return updateModelByFilter();
}

QString Filter::priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo)
{
    static const QRegularExpression regex("^[0-9]+$");

    if(inputTo->text().length() != 0 && !regex.match(inputTo->text()).hasMatch())
    {
        inputTo->setText("");
        return "";
    }

    if(inputDo->text().length() != 0 && !regex.match(inputDo->text()).hasMatch())
    {
        inputDo->setText("");
        return "";
    }

    priceTo = inputTo->text(), priceDo = inputDo->text();
    return updateModelByFilter();
}

QString Filter::updateModelByFilter()
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

    return ("c_name in(" + filterCategory + ") and p_country in(" +
            filterCountry + ") and p_brand in(" + filterBrand + ") and (" + filterPrice + ")");
}

QString Filter::getFilterForList(const QStringList& list, const QString& nameColumCopare)
{
    return nameColumCopare + " in(" + QString(list.join(",")) + ")";
}
