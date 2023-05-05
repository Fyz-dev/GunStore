#include "formpeople.h"
#include "ui_formpeople.h"
#include <QDateTime>

FormPeople::FormPeople(const QString& INN, const QString& FIO, BaseModel* model, QWidget *parent) : FormPeople(INN, model, parent)
{
    ui->labelTop->setText(FIO);
    ui->labelTopBottom->setText("ІНН:" + INN);

    ui->count->setText(model->getOneCell(QString("select sum(listP_count) from listproduct join sales using(id_sales) where inn = %1").arg(identifier)));
    ui->sum->setText(model->getOneCell(QString("select sum(listP_count*p_priceOne) from product join listproduct using(id_product) join sales using(id_sales) where inn = %1").arg(identifier)));
    model->updateModelViaQuery(QString("select id_sales, date_time, count(*), sum(listP_count * p_priceOne) from product join listproduct using(id_product) join sales using(id_sales) where inn = %1 group by 1").arg(identifier));

    QSqlRelationalTableModel* modelData = model->getModelData();

    list.clear();
    for (int i = 0; i < modelData->rowCount(); ++i)
        list.append(new ElementOrder(modelData->index(i, 0).data().toString(),
                                     modelData->index(i, 1).data().toDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                     modelData->index(i, 2).data().toString(),
                                     modelData->index(i, 3).data().toString(), static_cast<BuyerModel*>(model),this));

    addToView();
}

FormPeople::FormPeople(const QString& identifier, const QString& SupplierName, const QString& edrpou, BaseModel* model, QWidget *parent) :
    FormPeople(identifier, model, parent)
{
    ui->labelTop->setText(SupplierName);
    ui->labelTopBottom->setText("ЄДРПОУ: " + edrpou);

    ui->count->setText(model->getOneCell(QString("select sum(listS_count) from listsupply join waybill using(id_waybill) where id_supplier = %1").arg(identifier)));
    ui->sum->setText(model->getOneCell(QString("select sum(listS_priceCount*listS_count) from listsupply join waybill using(id_waybill) where id_supplier = %1").arg(identifier)));
    model->updateModelViaQuery(QString("select waybillDate, count(DISTINCT id_product), sum(listS_count*listS_priceCount) from listsupply join waybill using(id_waybill) where id_supplier = %1 group by 1").arg(identifier));

    QSqlRelationalTableModel* modelData = model->getModelData();

    list.clear();
    for (int i = 0; i < modelData->rowCount(); ++i)
        list.append(new ElementOrder(identifier,
                                     modelData->index(i, 0).data().toString(),
                                     modelData->index(i, 1).data().toString(),
                                     modelData->index(i, 2).data().toString(),
                                     static_cast<SupplierModel*>(model), this));

    addToView();
}

FormPeople::FormPeople(const QString& identifier, BaseModel* model, QWidget *parent) :
    QWidget(parent),
    model(model),
    identifier(identifier),
    ui(new Ui::FormPeople)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");
}

void FormPeople::addToView()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    for (ElementOrder* item : list)
        layout->insertWidget(0, item);
}

FormPeople::~FormPeople()
{
    delete model;
    delete ui;
}
