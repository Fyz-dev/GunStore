#include "menueditproduct.h"
#include "ui_menueditproduct.h"

menuEditProduct::menuEditProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuEditProduct)
{
    ui->setupUi(this);
}

menuEditProduct::~menuEditProduct()
{
    delete ui;
}
