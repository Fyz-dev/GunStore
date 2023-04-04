#include "addproductdialog.h"
#include "ui_addproductdialog.h"

AddProductDialog::AddProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}
