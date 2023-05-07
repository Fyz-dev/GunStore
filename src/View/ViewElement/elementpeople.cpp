#include "elementpeople.h"
#include "ui_elementpeople.h"
#include "formpeople.h"
#include "formwithbuttonback.h"
#include "buyermodel.h"
#include "suppliermodel.h"

ElementPeople::ElementPeople(const QString& INN, const QString& FIO, const QString& numberPhone, const QString& address, ConnectionHandler* connectionHandler, QWidget *parent) :
    ElementPeople(INN, numberPhone, address, connectionHandler, parent)
{
    title = FIO;
    ui->labelTitle->setText(FIO);
    ui->labelTitleBottom->setText("ІНН: " + INN);

    people = People::Buyer;
}

ElementPeople::ElementPeople(const QString& idSupplier, const QString& SupplierName, const QString& edrpou, const QString& numberPhone, const QString& address, ConnectionHandler* connectionHandler, QWidget *parent) :
    ElementPeople(idSupplier, numberPhone, address, connectionHandler, parent)
{
    title = SupplierName;
    titleBottom = edrpou;
    ui->labelTitle->setText(SupplierName);
    ui->labelTitleBottom->setText("ЄДРПОУ: " + edrpou);

    people = People::Supplier;
}

ElementPeople::ElementPeople(const QString& idWorker, const QString& FIO, const QString& position, const QString& numberPhone, const QString& address, QWidget *parent, ConnectionHandler* connectionHandler) :
    ElementPeople(idWorker, numberPhone, address, connectionHandler, parent)
{
    ui->labelTitle->setText(FIO);
    ui->labelTitleBottom->setText("Позиція: " + position);

    people = People::Employees;
}

//Base construct
ElementPeople::ElementPeople(const QString& identifier, const QString& numberPhone, const QString& address, ConnectionHandler* connectionHandler, QWidget* parent) :
    QWidget(parent),
    identifier(identifier),
    connectionHandler(connectionHandler),
    ui(new Ui::ElementPeople)
{
    ui->setupUi(this);

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

void ElementPeople::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    switch (people)
    {
    case People::Buyer:
        FormWithButtonBack::pushToView({new FormPeople(identifier, title, new BuyerModel(connectionHandler), this)});
        break;
    case People::Supplier:
        FormWithButtonBack::pushToView({new FormPeople(identifier, new SupplierModel(connectionHandler), this)});
        break;
    case People::Employees:
        break;
    }
}

ElementPeople::~ElementPeople()
{
    delete ui;
}
