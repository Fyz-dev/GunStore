#include "elementorder.h"
#include "ui_elementorder.h"
#include "formwithbuttonback.h"
#include "formwithtable.h"

ElementOrder::ElementOrder(const QString& identifier, const QString& Title, const QString& count, const QString sum, BuyerModel* model, QWidget *parent) :
    ElementOrder(identifier, count, sum, model, parent)
{
    ui->labelTitle->setText("Замовлення від " + Title);
}

ElementOrder::ElementOrder(const QString& identifier, const QString& date, const QString& count, const QString sum, SupplierModel* model, QWidget *parent) :
    ElementOrder(identifier, count, sum, (BaseModel*)model, parent)
{
    this->date = date;
    ui->labelTitle->setText("Постачання від " + date);
}

ElementOrder::ElementOrder(const QString& identifier, const QString& count, const QString sum, BaseModel* model, QWidget *parent) :
    QWidget(parent),
    identifier(identifier),
    model(model),
    count(count),
    sum(sum),
    ui(new Ui::ElementOrder)
{
    ui->setupUi(this);

    ui->labelCount->setText("Кількість: " + count + " од.");
    ui->labelSum->setText("Сума: " + sum + " грн.");
}

void ElementOrder::enterEvent(QEnterEvent* event)
{
    Q_UNUSED(event);
    ui->widget->setStyleSheet("QWidget#widget{ border-radius: 10px; background-color: #41444a; }");
}

void ElementOrder::leaveEvent(QEvent* event)
{
    Q_UNUSED(event);
    ui->widget->setStyleSheet("QWidget#widget{ border-radius: 10px; background-color: #202124; }");
}

void ElementOrder::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(BuyerModel* buyerModel = dynamic_cast<BuyerModel*>(model))
        FormWithButtonBack::pushToView({new FormWithTable(identifier, ui->labelTitle->text(), sum, buyerModel, this)});
    else if(SupplierModel* supplierModel = dynamic_cast<SupplierModel*>(model))
        FormWithButtonBack::pushToView({new FormWithTable(identifier, date, sum, supplierModel, this)});
}

ElementOrder::~ElementOrder()
{
    delete ui;
}
