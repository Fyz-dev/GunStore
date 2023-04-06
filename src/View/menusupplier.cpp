#include "menusupplier.h"
#include "ui_menusupplier.h"

MenuSupplier::MenuSupplier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuSupplier)
{
    ui->setupUi(this);
}

MenuSupplier::~MenuSupplier()
{
    delete ui;
}
