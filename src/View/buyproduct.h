#ifndef BUYPRODUCT_H
#define BUYPRODUCT_H

#include <QWidget>

namespace Ui {
class BuyProduct;
}

class BuyProduct : public QWidget
{
    Q_OBJECT

public:
    explicit BuyProduct(QWidget *parent = nullptr);
    ~BuyProduct();

private:
    Ui::BuyProduct *ui;
};

#endif // BUYPRODUCT_H
