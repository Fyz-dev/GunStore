#include "addbuyer.h"
#include "ui_addbuyer.h"

AddBuyer::AddBuyer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBuyer)
{
    ui->setupUi(this);
}

AddBuyer::~AddBuyer()
{
    delete ui;
}
