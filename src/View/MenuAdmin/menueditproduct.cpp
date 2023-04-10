#include "menueditproduct.h"
#include "ui_menueditproduct.h"

MenuEditProduct::MenuEditProduct(MenuEditProductViewModel* menuEditProductViewModel, QWidget *parent) :
    menuEditProductViewModel(menuEditProductViewModel),
    QWidget(parent),
    ui(new Ui::MenuEditProduct)
{
    ui->setupUi(this);
}

MenuEditProduct::~MenuEditProduct()
{
    delete ui;
}
