#include "addnewsupplier.h"
#include "ui_addnewsupplier.h"

AddNewSupplier::AddNewSupplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewSupplier)
{
    ui->setupUi(this);
}

AddNewSupplier::~AddNewSupplier()
{
    delete ui;
}
