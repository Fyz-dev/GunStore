#include "ordering.h"
#include "ui_ordering.h"

Ordering::Ordering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ordering)
{
    ui->setupUi(this);
    connected();
}

void Ordering::connected()
{
    connect(ui->buttonBack, &QPushButton::clicked, this, [&]()
    {
        emit closeMe();
    });
}

Ordering::~Ordering()
{
    delete ui;
}
