#include "menueditproduct.h"
#include "ui_menueditproduct.h"

MenuEditProduct::MenuEditProduct(MenuEditProductViewModel* menuEditProductViewModel, QWidget *parent) :
    menuEditProductViewModel(menuEditProductViewModel),
    QWidget(parent),
    ui(new Ui::MenuEditProduct)
{
    ui->setupUi(this);
    connected();

    ui->tableViewProduct->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewProduct->setPalette(QPalette(QPalette::WindowText, Qt::white));

    ui->comboBoxIsDelete->addItems({"Наявні товари", "Видалені товари"});

    menuEditProductViewModel->update(QString::number(ui->comboBoxIsDelete->currentIndex()));
    ui->tableViewProduct->setItemDelegate(menuEditProductViewModel->getDelegate());
}

void MenuEditProduct::modelChangedSlots(QAbstractTableModel* modelData)
{
    ui->tableViewProduct->setModel(nullptr);
    ui->tableViewProduct->setModel(modelData);
    ui->tableViewProduct->hideColumn(0);
    ui->tableViewProduct->hideColumn(9);
}

void MenuEditProduct::addCheckBoxSlots(QCheckBox* checkBox, const LayoutState& layoutName)
{
    connect(checkBox, &QCheckBox::stateChanged, this, [&](const int& state)
    {
        emit checkBoxEnabledSignals(state, sender(), QString::number(ui->comboBoxIsDelete->currentIndex()));
    });

    switch (layoutName)
    {
    case LayoutState::CATEGORY:
        ui->frameCategorys->layout()->addWidget(checkBox);
        break;
    case LayoutState::COUNTRY:
        ui->frameCountries->layout()->addWidget(checkBox);
        break;
    case LayoutState::BRAND:
        ui->frameBrands->layout()->addWidget(checkBox);
        break;
    }
}

//Добавляем характеристики в отображение
void MenuEditProduct::addInfoProductSlots(QWidget* widget)
{
    if(widget == nullptr)
    {
        ui->verticalLayout_16->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        return;
    }

    ui->infoSelectProduct->layout()->addWidget(widget);
}

void MenuEditProduct::clearCheckBoxSlots()
{
    deleteWidget(ui->frameCategorys->layout());
    deleteWidget(ui->frameCountries->layout());
    deleteWidget(ui->frameBrands->layout());
}

void MenuEditProduct::priceFilterChangedSlots()
{
    emit priceFilterChangedSignals(ui->inputTo, ui->inputDo, QString::number(ui->comboBoxIsDelete->currentIndex()));
}

void MenuEditProduct::clearLableSlots()
{
    ui->tableViewProduct->hideColumn(0);
    ui->tableViewProduct->hideColumn(9);
    deleteWidget(ui->infoSelectProduct->layout());
}

void MenuEditProduct::deleteWidget(QLayout* layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}

void MenuEditProduct::showMessageBox()
{
    QMessageBox::information(this, tr("Увага!"), tr("Зміни внесено до бази даних."));
}

void MenuEditProduct::show()
{
    menuEditProductViewModel->update(QString::number(ui->comboBoxIsDelete->currentIndex()));
}

void MenuEditProduct::hide() {}

void MenuEditProduct::connected()
{
    //Button
    connect(ui->buttonAccept, &QPushButton::clicked, this, [&]()
    {
        menuEditProductViewModel->applyChanges();
        menuEditProductViewModel->update(QString::number(ui->comboBoxIsDelete->currentIndex()));
    });

    connect(ui->buttonAddNewProduct, &QPushButton::clicked, this, [=]()
    {
        emit openAddNewProductDialogSignals();
    });

    connect(ui->buttonDeleteProduct, &QPushButton::clicked, this, [&]()
    {
        if(ui->tableViewProduct->currentIndex().isValid())
        {
            menuEditProductViewModel->addItemToRemove(ui->tableViewProduct->currentIndex().row());
            ui->tableViewProduct->update();
        }
    });

    connect(ui->comboBoxIsDelete, &QComboBox::currentIndexChanged, this, [&](const int& i)
    {
        menuEditProductViewModel->update(QString::number(i));
    });

    connect(this, &MenuEditProduct::checkBoxEnabledSignals, menuEditProductViewModel, &MenuEditProductViewModel::checkBoxEnabledSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::showMessageBoxSignals, this, &MenuEditProduct::showMessageBox);
    connect(ui->inputTo, &QLineEdit::textChanged, this, &MenuEditProduct::priceFilterChangedSlots);
    connect(ui->inputDo, &QLineEdit::textChanged, this, &MenuEditProduct::priceFilterChangedSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::modelChangedSignal, this, &MenuEditProduct::modelChangedSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::addCheckBoxSignal, this, &MenuEditProduct::addCheckBoxSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::clearCheckBoxSignal, this, &MenuEditProduct::clearCheckBoxSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::addInfoProductSignal, this, &MenuEditProduct::addInfoProductSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::clearLableSignal, this, &MenuEditProduct::clearLableSlots);
    connect(this, &MenuEditProduct::priceFilterChangedSignals, menuEditProductViewModel, &MenuEditProductViewModel::priceFilterChangedSlots);

    connect(ui->tableViewProduct, &QTableView::clicked, this, [&](const QModelIndex& i)
    {
        menuEditProductViewModel->selectedElemTableViewSlots(i, false);
    });
}

MenuEditProduct::~MenuEditProduct()
{
    delete ui;
}
