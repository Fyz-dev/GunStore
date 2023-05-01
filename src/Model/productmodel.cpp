#include "productmodel.h"

ProductModel::ProductModel(ConnectionHandler* connection) : BaseModel(connection)
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

void ProductModel::buyProduct(const QString& nameSupplier, QList<ElementBuyProduct*>& listElement)
{
//    qDebug() << nameSupplier;
//    qDebug() << QString("INSERT INTO waybill(id_worker, id_supplier, waybillDate) VALUES(%1, (select id_supplier from supplier where sup_name = '%2'), CURDATE())").arg(connection->getIdWorker(), nameSupplier);
    requestBD(QString("INSERT INTO waybill(id_worker, id_supplier, waybillDate) VALUES(%1, (select id_supplier from supplier where sup_name = '%2'), CURDATE())").arg(connection->getIdWorker(), nameSupplier));

    QString idWayBill = QString::number(lastInsertId);

    for (ElementBuyProduct* element : listElement)
    {
        QString countThisElem = QString::number(element->getCount());
        requestBD(QString("INSERT INTO listsupply(id_waybill, id_product, listS_priceCount, listS_count) VALUES(%1, %2, %3, %4)").arg(idWayBill, element->getIdProduct(), element->getPrice(), countThisElem));
        requestBD("call addCountProduct(" + element->getIdProduct() + "," + countThisElem + ")");
    }
}
