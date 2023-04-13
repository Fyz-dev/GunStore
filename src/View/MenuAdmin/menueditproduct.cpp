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

    menuEditProductViewModel->update();

    ui->tableViewProduct->hideColumn(0);
}

void MenuEditProduct::modelChangedSlots(QAbstractTableModel* modelData)
{
    ui->tableViewProduct->setModel(nullptr);
    ui->tableViewProduct->setModel(modelData);
}

void MenuEditProduct::addCheckBoxSlots(QCheckBox* checkBox, const LayoutState& layoutName)
{
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

void MenuEditProduct::addInfoProductSlots(QLabel* label, QLineEdit* lineEdit)
{
    if(label == nullptr)
    {
        ui->verticalLayout_16->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        return;
    }

    QFrame* frame = new QFrame;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    frame->setLayout(layout);
    ui->infoSelectProduct->layout()->addWidget(frame);
}

void MenuEditProduct::clearCheckBoxSlots()
{
    deleteWidget(ui->frameCategorys->layout());
    deleteWidget(ui->frameCountries->layout());
    deleteWidget(ui->frameBrands->layout());
}

void MenuEditProduct::priceFilterChangedSlots()
{
    emit priceFilterChangedSignals(ui->inputTo, ui->inputDo);
}

void MenuEditProduct::clearLableSlots()
{
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

void MenuEditProduct::connected()
{
    //Button
    connect(ui->buttonAccept, &QPushButton::clicked, menuEditProductViewModel, &MenuEditProductViewModel::applyChanges);

    connect(ui->inputTo, &QLineEdit::textChanged, this, &MenuEditProduct::priceFilterChangedSlots);
    connect(ui->inputDo, &QLineEdit::textChanged, this, &MenuEditProduct::priceFilterChangedSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::modelChangedSignal, this, &MenuEditProduct::modelChangedSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::addCheckBoxSignal, this, &MenuEditProduct::addCheckBoxSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::clearCheckBoxSignal, this, &MenuEditProduct::clearCheckBoxSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::addInfoProductSignal, this, &MenuEditProduct::addInfoProductSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::clearLableSignal, this, &MenuEditProduct::clearLableSlots);
    connect(this, &MenuEditProduct::priceFilterChangedSignals, menuEditProductViewModel, &MenuEditProductViewModel::priceFilterChangedSlots);
    connect(ui->tableViewProduct, &QTableView::doubleClicked, this, [&](const QModelIndex& i)
    {
        menuEditProductViewModel->selectedElemTableViewSlots(i, false);
    });
}

MenuEditProduct::~MenuEditProduct()
{
    delete ui;
}
