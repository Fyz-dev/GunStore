#include "formwithtable.h"
#include "ui_formwithtable.h"

FormWithTable::FormWithTable(const QString& identifier, const QString& title, const QString& sum, BuyerModel* buyerModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWithTable)
{
    ui->setupUi(this);
    ui->labelTitle->setText(title);
    ui->count->setText(buyerModel->getOneCell(QString("select sum(listP_count) from listproduct where id_sales = %1").arg(identifier)));
    ui->sum->setText(sum);

    buyerModel->updateModelViaQuery(QString("select p_name as 'Назва товару', p_priceOne as 'Ціна за одиницю (грн.)', p_brand as 'Бренд', p_weight as 'Віга (г.)', p_package as 'Упаковка', p_country as 'Країна', listP_count as 'Кількість (од.)' from product join listproduct using(id_product) join sales using(id_sales) where id_sales = %1").arg(identifier));
    ui->tableView->setModel(buyerModel->getModelData());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

FormWithTable::~FormWithTable()
{
    delete ui;
}
