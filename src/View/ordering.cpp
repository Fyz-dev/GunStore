#include "ordering.h"
#include "ui_ordering.h"

Ordering::Ordering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ordering)
{
    ui->setupUi(this);
}

Ordering::~Ordering()
{
    delete ui;
}
