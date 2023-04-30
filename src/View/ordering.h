#ifndef ORDERING_H
#define ORDERING_H

#include "productmodel.h"
#include "filter.h"

#include <QDialog>

namespace Ui {
class Ordering;
}

class Ordering : public QDialog
{
    Q_OBJECT

public:
    explicit Ordering(QHash<int, int>& listProduct, ConnectionHandler* connectionHandler, QWidget *parent = nullptr);
    ~Ordering();

signals:
    void closeMe();

private slots:
    void next();

private:
    void updateSumAndCount();
    void deleteProduct();

private:
    Ui::Ordering *ui;
    QHash<int, int>& listProduct;
    ProductModel* productModel;
    Filter* filter;
    QWidget* parent;
};

#endif // ORDERING_H
