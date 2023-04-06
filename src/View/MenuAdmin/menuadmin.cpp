#include "menuadmin.h"
#include "ui_menuadmin.h"

MenuAdmin::MenuAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuAdmin)
{
    ui->setupUi(this);
}

MenuAdmin::~MenuAdmin()
{
    delete ui;
}
