#ifndef ADDBUYER_H
#define ADDBUYER_H

#include "productmodel.h"

#include <QWidget>

namespace Ui {
class AddBuyer;
}

class AddBuyer : public QWidget
{
    Q_OBJECT

public:
    explicit AddBuyer(ProductModel* productModel, QHash<int, int>& listProduct, QWidget *parent = nullptr);
    ~AddBuyer();

private slots:
    void buttonOrder_clicked();
    void comboBoxIndexChanged(const int& i);
    void inputNewFIO();

private:
    void connected();
    void setEditable(bool isEdit);

private:
    Ui::AddBuyer *ui;
    ProductModel* productModel;
    QHash<int, int>& listProduct;
};

#endif // ADDBUYER_H
