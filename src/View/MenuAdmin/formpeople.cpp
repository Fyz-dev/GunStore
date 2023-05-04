#include "formpeople.h"
#include "ui_formpeople.h"
#include <QDateTime>

FormPeople::FormPeople(const QString& INN, const QString& FIO, BaseModel* model, QWidget *parent) :
    QWidget(parent),
    model(model),
    identifier(INN),
    ui(new Ui::FormPeople)
{
    ui->setupUi(this);

    ui->labelTop->setText(FIO);
    ui->labelTopBottom->setText("ІНН:" + INN);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");
    update();
}

void FormPeople::update()
{
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

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    for (ElementOrder* item : list)
        layout->insertWidget(0, item);
}

FormPeople::~FormPeople()
{
    delete model;
    delete ui;
}
