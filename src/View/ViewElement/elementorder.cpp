#include "elementorder.h"
#include "ui_elementorder.h"

ElementOrder::ElementOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementOrder)
{
    ui->setupUi(this);
}

ElementOrder::~ElementOrder()
{
    delete ui;
}
