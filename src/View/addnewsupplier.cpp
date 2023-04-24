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
        this->supplierModel->requestBD("INSERT INTO supplier(sup_name, sup_edrpou, sup_phoneNum, sup_address, sup_bank) VALUES('" + ui->inputFullNameSupplier->text() + "'," + ui->inputEdrpou->text() + ",'" + ui->inpuNumberPhone->text() + "','" + ui->inpuAddress->text() + "','" + ui->inpuBank->text() + "')");
        this->close();
    });
}

AddNewSupplier::~AddNewSupplier()
{
    delete ui;
}
