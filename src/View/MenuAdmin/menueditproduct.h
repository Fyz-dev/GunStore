#ifndef MENUEDITPRODUCT_H
#define MENUEDITPRODUCT_H

#include <QWidget>

namespace Ui {
class menuEditProduct;
}

class menuEditProduct : public QWidget
{
    Q_OBJECT

public:
    explicit menuEditProduct(QWidget *parent = nullptr);
    ~menuEditProduct();

private:
    Ui::menuEditProduct *ui;
};

#endif // MENUEDITPRODUCT_H
