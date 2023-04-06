#include "menuemployees.h"
#include "ui_menuemployees.h"

MenuEmployees::MenuEmployees(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuEmployees)
{
    ui->setupUi(this);
}

MenuEmployees::~MenuEmployees()
{
    delete ui;
}
