#include "menusupplier.h"
#include "ui_menusupplier.h"

MenuSupplier::MenuSupplier(SupplierModel* supplierModel, QWidget *parent) :
    QWidget(parent),
    supplierModel(supplierModel),
    ui(new Ui::MenuSupplier)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");

    update();

    connect(ui->buttonAdd, &QPushButton::clicked, this, [&]()
    {
        emit openAddSupplier();
    });
}

void MenuSupplier::update()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    for (ElementPeople* item : supplierModel->updateInfoBuyPeople(this))
        layout->insertWidget(layout->count()-1, item);

    ui->count->setText(supplierModel->getOneCell("select sum(listS_count) from listsupply"));
    ui->sum->setText(supplierModel->getOneCell("select sum(listS_priceCount*listS_count) from listsupply"));
}

MenuSupplier::~MenuSupplier()
{
    delete ui;
}
