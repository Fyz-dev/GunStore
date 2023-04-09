#ifndef BUYPRODUCTVIEWMODEL_H
#define BUYPRODUCTVIEWMODEL_H

#include "baseviewmodel.h"
#include "productmodel.h"
#include "elementbuyproduct.h"

#include <QStandardItemModel>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QTableView>

class BuyProductViewModel : public QObject, public BaseViewModel
{
    Q_OBJECT

public:
    BuyProductViewModel(ProductModel* productModel);
    void update() override;
    void printReport(const QString& sumCount, const QString& sumPrice);

public slots:
    void changedComboBoxSlots(const int& i);
    void deleteElementBuyProduct(ElementBuyProduct* element);
    void changedCountPriceSlots();
    void buyProducts();

signals:
    void updateComboBoxSignals(const QList<QString>& list);
    void addElemntByViewSignals(ElementBuyProduct* element);
    void addComboBoxSignals(const QString& itemName);
    void updateSumInfoSignals(const int& sumCount, const double& sumPrice);
    void messageBoxShowSignals();

private:
    ProductModel* productModel;
    QList<ElementBuyProduct*> listElement;
};

#endif // BUYPRODUCTVIEWMODEL_H
