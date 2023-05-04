#include "menubuyer.h"
#include "ui_menubuyer.h"
#include "elementpeople.h"

MenuBuyer::MenuBuyer(BuyerModel* buyerModel, QWidget *parent) :
    QWidget(parent),
    buyerModel(buyerModel),
    ui(new Ui::MenuBuyer)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");

    update();
}

void MenuBuyer::update()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    for (ElementPeople* elementPeople : buyerModel->updateInfoBuyPeople(this))
        layout->insertWidget(layout->count()-1, elementPeople);

    ui->count->setText(buyerModel->getOneCell("select sum(listP_count) from listproduct"));
    ui->sum->setText(buyerModel->getOneCell("select sum(p_priceOne*listP_count) from product join listproduct using(id_product)"));
}

MenuBuyer::~MenuBuyer()
{
    delete ui;
}
