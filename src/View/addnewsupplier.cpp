#include "addnewsupplier.h"
#include "ui_addnewsupplier.h"

AddNewSupplier::AddNewSupplier(SupplierModel* supplierModel, QWidget *parent) :
    supplierModel(supplierModel),
    QDialog(parent),
    ui(new Ui::AddNewSupplier)
{
    ui->setupUi(this);


    connect(ui->buttonAddSupplier, &QPushButton::clicked, this, [&]()
    {
        supplierModel->requestBD("");
    });
}

AddNewSupplier::~AddNewSupplier()
{
    delete ui;
}
