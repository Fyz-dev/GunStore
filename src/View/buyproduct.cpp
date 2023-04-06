#include "buyproduct.h"
#include "ui_buyproduct.h"

BuyProduct::BuyProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyProduct)
{
    ui->setupUi(this);
}

BuyProduct::~BuyProduct()
{
    delete ui;
}
