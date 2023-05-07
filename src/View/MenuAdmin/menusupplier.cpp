#include "menusupplier.h"
#include "ui_menusupplier.h"

MenuSupplier::MenuSupplier(SupplierModel* supplierModel, QWidget *parent) :
    QWidget(parent),
    supplierModel(supplierModel),
    ui(new Ui::MenuSupplier)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");
    ui->comboBoxIsDelete->addItems({"Наявні постачальники", "Видалені постачальники"});

    update();

    connect(ui->buttonAdd, &QPushButton::clicked, this, [&]()
    {
        emit openAddSupplier();
    });

    connect(ui->comboBoxIsDelete, &QComboBox::currentIndexChanged, this, [&](const int& i)
    {
        update();
    });
}

void MenuSupplier::show()
{
    update();
    QWidget::show();
}

void MenuSupplier::hide()
{
    QWidget::hide();
}

void MenuSupplier::update()
{
    QString currentIndex = QString::number(ui->comboBoxIsDelete->currentIndex());

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    for (ElementPeople* item : supplierModel->updateInfoBuyPeople(this, currentIndex))
        layout->insertWidget(layout->count()-1, item);

    ui->count->setText(supplierModel->getOneCell(QString("select sum(listS_count) from listsupply join waybill using(id_waybill) join supplier using(id_supplier) where isDelete = %1").arg(currentIndex)));
    ui->sum->setText(supplierModel->getOneCell(QString("select sum(listS_priceCount*listS_count) from listsupply join waybill using(id_waybill) join supplier using(id_supplier) where isDelete = %1").arg(currentIndex)));
}

MenuSupplier::~MenuSupplier()
{
    delete ui;
}
