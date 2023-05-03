#include "menubuyer.h"
#include "ui_menubuyer.h"
#include "elementpeople.h"

MenuBuyer::MenuBuyer(BuyerModel* buyerModel, QWidget *parent) :
    QWidget(parent),
    buyerModel(buyerModel),
    ui(new Ui::MenuBuyer)
{
    ui->setupUi(this);
    update();
}

void MenuBuyer::update()
{
    for (ElementPeople* elementPeople : buyerModel->updateInfoBuyPeople(this))
        ui->verticalLayout->insertWidget(ui->verticalLayout->count()-1, elementPeople);
}

MenuBuyer::~MenuBuyer()
{
    delete ui;
}
