#include "menureport.h"
#include "ui_menureport.h"

MenuReport::MenuReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuReport)
{
    ui->setupUi(this);
}

MenuReport::~MenuReport()
{
    delete ui;
}
