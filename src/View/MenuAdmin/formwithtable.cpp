#include "formwithtable.h"
#include "ui_formwithtable.h"

FormWithTable::FormWithTable(const QString& INN, BuyerModel* buyerModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWithTable)
{
    ui->setupUi(this);
}

FormWithTable::~FormWithTable()
{
    delete ui;
}
