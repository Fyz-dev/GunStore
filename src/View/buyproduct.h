#ifndef BUYPRODUCT_H
#define BUYPRODUCT_H

#include "buyproductviewmodel.h"

#include <QWidget>
#include <QComboBox>

namespace Ui {
class BuyProduct;
}

class BuyProduct : public QWidget
{
    Q_OBJECT

public:
    explicit BuyProduct(BuyProductViewModel* buyProductViewModel, QWidget *parent = nullptr);
    ~BuyProduct();

public slots:
    void updateComboBoxSlots(const QList<QString>& list);
    void addElemntByView(ElementBuyProduct* element);
    void updateSumInfoSlots(const int& sumCount, const double& sumPrice);
    void messageBoxShow();

private:
    void connected();

private:
    Ui::BuyProduct *ui;
    BuyProductViewModel* buyProductViewModel;
};

#endif // BUYPRODUCT_H
