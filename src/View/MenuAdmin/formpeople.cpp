#include "formpeople.h"
#include "ui_formpeople.h"
#include "formwithbuttonback.h"
#include "addbuyer.h"
#include "addnewsupplier.h"
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

FormPeople::FormPeople(const QString& identifier, SupplierModel* model, QWidget *parent) :
    FormPeople(identifier, (BaseModel*)model, parent)
{
    updateSupplier();

    if(model->getOneCell(QString("select isDelete from supplier where id_supplier = %1").arg(identifier)) == "0")
    {
        ui->buttonDelete->show();

        connect(ui->buttonDelete, &QPushButton::clicked, this, [=]()
        {
            model->requestBD(QString("UPDATE supplier SET isDelete = 1 where id_supplier = %1").arg(identifier));
            FormWithButtonBack::clearStack();
        });
    }
    else
    {
        ui->buttonReturn->show();

        connect(ui->buttonReturn, &QPushButton::clicked, this, [=]()
        {
            model->requestBD(QString("UPDATE supplier SET isDelete = 0 where id_supplier = %1").arg(identifier));
            FormWithButtonBack::clearStack();
        });
    }
}

FormPeople::FormPeople(const QString& identifier, BaseModel* model, QWidget *parent) :
    QWidget(parent),
    model(model),
    identifier(identifier),
    ui(new Ui::FormPeople)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");

    connect(ui->buttonDetails, &QPushButton::clicked, this, &FormPeople::buttonDetails_clicked);

    ui->buttonReturn->hide();
    ui->buttonDelete->hide();
}

void FormPeople::buttonDetails_clicked()
{
    if(dynamic_cast<BuyerModel*>(model))
    {
        model->updateModelViaQuery(QString("select full_name, phone_number, email, city, details, license from buyer join address using(id_address) where inn = %1;").arg(identifier));
        QSqlRelationalTableModel* modelData = model->getModelData();

        FormWithButtonBack::pushToView({new AddBuyer(modelData->index(0, 0).data().toString(),
                                        identifier, modelData->index(0, 1).data().toString(),
                                        modelData->index(0, 2).data().toString(),
                                        modelData->index(0, 3).data().toString(),
                                        modelData->index(0, 4).data().toString(),
                                        modelData->index(0, 5).data().toString(), this)});
    }
    else
    {
        FormWithButtonBack::pushToView({new AddNewSupplier(identifier, static_cast<SupplierModel*>(model), this)});
    }
}

void FormPeople::updateSupplier()
{
    ui->labelTop->setText(model->getOneCell(QString("select sup_name from supplier where id_supplier = %1").arg(identifier)));
    ui->labelTopBottom->setText("ЄДРПОУ: " + model->getOneCell(QString("select sup_edrpou from supplier where id_supplier = %1").arg(identifier)));

    ui->count->setText(model->getOneCell(QString("select sum(listS_count) from listsupply join waybill using(id_waybill) where id_supplier = %1").arg(identifier)));
    ui->sum->setText(model->getOneCell(QString("select sum(listS_priceCount*listS_count) from listsupply join waybill using(id_waybill) where id_supplier = %1").arg(identifier)));
    model->updateModelViaQuery(QString("select waybillDate, count(DISTINCT id_product), sum(listS_count*listS_priceCount) from listsupply join waybill using(id_waybill) where id_supplier = %1 group by 1").arg(identifier));

    QSqlRelationalTableModel* modelData = model->getModelData();

    for(ElementOrder* item : list)
        delete item;
    list.clear();

    for (int i = 0; i < modelData->rowCount(); ++i)
        list.append(new ElementOrder(identifier,
                                     modelData->index(i, 0).data().toString(),
                                     modelData->index(i, 1).data().toString(),
                                     modelData->index(i, 2).data().toString(),
                                     static_cast<SupplierModel*>(model), this));

    addToView();
}

void FormPeople::show()
{
    if(dynamic_cast<SupplierModel*>(model))
        updateSupplier();

    QWidget::show();
}

void FormPeople::hide()
{
    QWidget::hide();
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
