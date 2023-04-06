#include "menubuyer.h"
#include "ui_menubuyer.h"

MenuBuyer::MenuBuyer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuBuyer)
{
    ui->setupUi(this);
}

MenuBuyer::~MenuBuyer()
{
    delete ui;
}
