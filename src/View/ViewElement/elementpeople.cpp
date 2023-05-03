#include "elementpeople.h"
#include "ui_elementpeople.h"

ElementPeople::ElementPeople(const QString& INN, const QString& FIO, const QString& numberPhone, const QString& address, QWidget *parent) :
    QWidget(parent),
    INN(INN),
    ui(new Ui::ElementPeople)
{
    ui->setupUi(this);

    ui->labelFIO->setText(FIO);
    ui->labelINN->setText("ІНН: " + INN);
    ui->labelPhone->setText("+38" + numberPhone);
    ui->labelAddress->setText(address);
}

void ElementPeople::enterEvent(QEnterEvent* event)
{
    Q_UNUSED(event);
    ui->widget->setStyleSheet("QWidget#widget{ border-radius: 10px; background-color: #41444a; }");
}

void ElementPeople::leaveEvent(QEvent* event)
{
    Q_UNUSED(event);
    ui->widget->setStyleSheet("QWidget#widget{ border-radius: 10px; background-color: #202124; }");
}

ElementPeople::~ElementPeople()
{
    delete ui;
}
