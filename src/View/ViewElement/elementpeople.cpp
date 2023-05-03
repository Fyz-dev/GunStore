#include "elementpeople.h"
#include "ui_elementpeople.h"

ElementPeople::ElementPeople(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementPeople)
{
    ui->setupUi(this);
}

ElementPeople::~ElementPeople()
{
    delete ui;
}
