#include "menusupplier.h"
#include "ui_menusupplier.h"

MenuSupplier::MenuSupplier(MenuSupplierViewModel* menuSupplierViewModel, QWidget *parent) :
    menuSupplierViewModel(menuSupplierViewModel),
    QWidget(parent),
    ui(new Ui::MenuSupplier)
{
    ui->setupUi(this);
    ui->tableViewSupplier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connected();

    menuSupplierViewModel->update();
    ui->tableViewSupplier->setItemDelegate(menuSupplierViewModel->getDelegate());
}

void MenuSupplier::connected()
{
    connect(menuSupplierViewModel, &MenuSupplierViewModel::modelChangedSignals, this, &MenuSupplier::modelChangedSlots);
    connect(ui->buttonAddSupplier, &QPushButton::clicked, this, [&]()
    {
        emit openAddSupplier();
    });

    connect(ui->buttonApplyChanges, &QPushButton::clicked, this, [&]()
    {
        menuSupplierViewModel->applyChanges();
        menuSupplierViewModel->update();
    });

    connect(ui->buttonRemoveSupplier, &QPushButton::clicked, this, [&]()
    {
        if(ui->tableViewSupplier->currentIndex().isValid())
            menuSupplierViewModel->addToRemove(ui->tableViewSupplier->currentIndex().row());
        ui->tableViewSupplier->update();
    });
}

void MenuSupplier::modelChangedSlots(QAbstractItemModel* model)
{
    ui->tableViewSupplier->setModel(nullptr);
    ui->tableViewSupplier->setModel(model);
    ui->tableViewSupplier->hideColumn(0);
}

MenuSupplier::~MenuSupplier()
{
    delete ui;
}
