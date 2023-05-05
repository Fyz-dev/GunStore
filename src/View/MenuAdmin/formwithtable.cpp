#include "formwithtable.h"
#include "ui_formwithtable.h"

FormWithTable::FormWithTable(const QString& identifier, const QString& title, const QString& sum, BuyerModel* buyerModel, QWidget *parent) :
    FormWithTable(identifier, sum, parent)
{
    ui->labelTitle->setText(title);
    ui->count->setText(buyerModel->getOneCell(QString("select sum(listP_count) from listproduct where id_sales = %1").arg(identifier)));

    buyerModel->updateModelViaQuery(QString("select p_name as 'Назва товару', p_priceOne as 'Ціна за одиницю (грн.)', p_brand as 'Бренд', p_weight as 'Вага (г.)', p_package as 'Упаковка', p_country as 'Країна', listP_count as 'Кількість (од.)' from product join listproduct using(id_product) join sales using(id_sales) where id_sales = %1").arg(identifier));

    ui->tableView->setModel(buyerModel->getModelData());
}

FormWithTable::FormWithTable(const QString& identifier, const QString& title, const QString& sum, SupplierModel* supplierModel, QWidget *parent) :
    FormWithTable(identifier, sum, parent)
{
    ui->labelTitle->setText("Постачання від " + title);
    ui->count->setText(supplierModel->getOneCell(QString("select sum(listS_count) from listsupply join waybill using(id_waybill) join product using(id_product) where id_supplier = %1 and waybillDate = '%2' group by waybillDate;").arg(identifier, title)));

    supplierModel->updateModelViaQuery(QString("select p_name as 'Назва товару', listS_priceCount as 'Ціна за одиницю (грн.)', p_brand as 'Бренд', p_weight as 'Вага (г.)', p_package as 'Упаковка', p_country as 'Країна', sum(listS_count) as 'Кількість (од.)' from listsupply join waybill using(id_waybill) join product using(id_product) where id_supplier = %1 and waybillDate = '%2' group by id_product;")
                                       .arg(identifier, title));

    ui->tableView->setModel(supplierModel->getModelData());
}

FormWithTable::FormWithTable(const QString& identifier, const QString& sum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWithTable)
{
    ui->setupUi(this);

    ui->sum->setText(sum);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QHeaderView::NoEditTriggers);
}

FormWithTable::~FormWithTable()
{
    delete ui;
}
