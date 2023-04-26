#include "buyproductviewmodel.h"
#include "printer.h"

BuyProductViewModel::BuyProductViewModel(ProductModel* productModel) : BaseViewModel("call getMainCharacteristicForProduct")
    ,productModel(productModel)
{}

void BuyProductViewModel::update()
{
    QList<QString> list, listSupplier;

    while(listElement.count() != 0)
    {
        delete listElement[0];
        listElement.remove(0);
    }
    changedCountPriceSlots();

    productModel->updateList(list, "select p_name from product");
    productModel->updateList(listSupplier, "select sup_name from supplier");
    emit updateComboBoxSignals(list, listSupplier);
}

void BuyProductViewModel::changedComboBoxSlots(const int& i)
{
    if(i == -1)
        return;

    QComboBox* senders = qobject_cast<QComboBox*>(sender());
    productModel->updateModelViaQuery(standartRequest + "('" + senders->itemText(i) + "')");
    listElement.append(new ElementBuyProduct(productModel->getModelData()));

    connect(listElement.last(), &ElementBuyProduct::deleteMe, this, &BuyProductViewModel::deleteElementBuyProduct);
    connect(listElement.last(), &ElementBuyProduct::changedCountPriceSignals, this, &BuyProductViewModel::changedCountPriceSlots);

    changedCountPriceSlots();

    senders->setCurrentIndex(-1);
    senders->removeItem(i);

    emit addElemntByViewSignals(listElement.last());
}

void BuyProductViewModel::deleteElementBuyProduct(ElementBuyProduct* element)
{
    for (int i = 0; i < listElement.count(); ++i)
    {
        if(listElement[i]->getNameProduct() == element->getNameProduct())
        {
            emit addComboBoxSignals(listElement[i]->getNameProduct());
            delete listElement[i];
            listElement.remove(i);
            changedCountPriceSlots();
            return;
        }
    }
}

void BuyProductViewModel::changedCountPriceSlots()
{
    int sumCount = 0;
    double sumPrice = 0;
    for (ElementBuyProduct* element : listElement)
    {
        sumCount += element->getCount();
        sumPrice += element->getSumPrice();
    }
    emit updateSumInfoSignals(sumCount, sumPrice);
}

void BuyProductViewModel::buyProducts(const QString& nameSupplier)
{
    if(listElement.count() == 0)
        return;

    productModel->buyProduct(nameSupplier, listElement);

    emit messageBoxShowSignals();
}

void BuyProductViewModel::printReport(const QString& sumCount, const QString& sumPrice)
{
    QTableView table;
    QStandardItemModel model;

    model.setHorizontalHeaderLabels({"Назава товару", "Бренд", "Кількість (од.)", "Ціна (грн.)"});
    for (int i = 0; i < listElement.count(); ++i)
    {
        model.setItem(i, 0, new QStandardItem(listElement[i]->getNameProduct()));
        model.setItem(i, 1, new QStandardItem(listElement[i]->getBrand()));
        model.setItem(i, 2, new QStandardItem(QString::number(listElement[i]->getCount())));
        model.setItem(i, 3, new QStandardItem(QString::number(listElement[i]->getSumPrice(), 'f', 2)));
    }
    table.setModel(&model);


    Printer printer;
    printer.printActOfSupply(&table, sumCount, sumPrice);
}
