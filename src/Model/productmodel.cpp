#include "productmodel.h"

ProductModel::ProductModel(QSqlDatabase* db) : BaseModel(db)
{}

void ProductModel::updateListFilter()
{
    updateList(listCategory, "select c_name from product join category using(id_category) group by id_category");
    updateList(listCountry, "select p_country from product group by p_country");
    updateList(listBrand, "select p_brand from product group by p_brand");
}

void ProductModel::updateList(QList<QString>& list, QString request)
{
   QSqlQuery* query = select(request);

   if(query == nullptr)
       return;

   list.clear();
   while(query->next())
       list.append(query->value(0).toString());

   delete query;
}

void ProductModel::createElementForDispleyCharact(QString request, bool lineEditIsReadOnly)
{
    QSqlQuery* query = select(request);

    if(query == nullptr)
        return;

    while(query->next())
    {
        ElementCharacteristic* element = new ElementCharacteristic(query->value(0).toString(),
        listChangedCharacteristic.contains(query->value(2).toInt()) ? listChangedCharacteristic.value(query->value(2).toInt()) : query->value(1).toString(),
        query->value(2).toInt(), lineEditIsReadOnly);

        connect(element, &ElementCharacteristic::changedValueSignals, this, &ProductModel::changedValueCharacteristicSlots);
        emit addInfoProductSignal(element);
    }

    delete query;
}

QList<QCheckBox*> ProductModel::createCheckBox(const QList<QString>& list)
{
    QList<QCheckBox*> listCheckBox;

    for(const QString& value : list)
    {
        QCheckBox* checkBox = new QCheckBox;
        checkBox->setText(value);
        checkBox->setToolTip(value);
        listCheckBox.append(checkBox);
    }

    return listCheckBox;
}

void ProductModel::setHeaderModel()
{
    modelData->setHeaderData(1, Qt::Horizontal, "Назва");
    modelData->setHeaderData(2, Qt::Horizontal, "Ціна(грн.)");
    modelData->setHeaderData(3, Qt::Horizontal, "Кількість(шт.)");
    modelData->setHeaderData(4, Qt::Horizontal, "Бренд");
    modelData->setHeaderData(5, Qt::Horizontal, "Вес(г.)");
    modelData->setHeaderData(6, Qt::Horizontal, "Упаковка");
    modelData->setHeaderData(7, Qt::Horizontal, "Країна");
    modelData->setHeaderData(8, Qt::Horizontal, "Категорія");
}

void ProductModel::changedValueCharacteristicSlots(const ElementCharacteristic* element)
{
    for(QHash<int, QString>::iterator i = listChangedCharacteristic.begin(); i != listChangedCharacteristic.end(); ++i)
    {
        if(element->getIdProductValue() == i.key())
        {
            i.value() = element->getValue();
            return;
        }

    }

    listChangedCharacteristic.insert(element->getIdProductValue(), element->getValue());
}

