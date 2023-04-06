#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(MainMenuViewModel* mainMenuViewModel, QWidget *parent) :
    mainMenuViewModel(mainMenuViewModel),
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    connected();

    ui->tableViewProduct->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewProduct->setSelectionMode(QAbstractItemView::SingleSelection);


    mainMenuViewModel->update();
}

void MainMenu::modelChangedSlots(QSqlTableModel* modelData)
{
    ui->tableViewProduct->setModel(nullptr);
    ui->tableViewProduct->setModel(modelData);
}

void MainMenu::addCheckBoxSlots(QCheckBox* checkBox, LayoutState& layoutName)
{
    switch (layoutName) {
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

void MainMenu::addInfoProductSlots(QLabel* label, QLineEdit* lineEdit)
{
    if(label == nullptr)
    {
        ui->verticalLayout_4->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        return;
    }

    QFrame* frame = new QFrame;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    frame->setLayout(layout);
    ui->infoSelectProduct->layout()->addWidget(frame);
}

void MainMenu::clearCheckBoxSlots()
{
    deleteWidget(ui->frameCategorys->layout());
    deleteWidget(ui->frameCountries->layout());
    deleteWidget(ui->frameBrands->layout());
}

void MainMenu::priceFilterChangedSlots()
{
    emit priceFilterChangetSignals(ui->inputTo, ui->inputDo);
}

void MainMenu::clearLableSlots()
{
    deleteWidget(ui->infoSelectProduct->layout());
}

void MainMenu::deleteWidget(QLayout* layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}

void MainMenu::connected()
{
    connect(ui->inputTo, &QLineEdit::textChanged, this, &MainMenu::priceFilterChangedSlots);
    connect(ui->inputDo, &QLineEdit::textChanged, this, &MainMenu::priceFilterChangedSlots);
    connect(mainMenuViewModel, &MainMenuViewModel::modelChangedSignal, this, &MainMenu::modelChangedSlots);
    connect(mainMenuViewModel, &MainMenuViewModel::addCheckBoxSignal, this, &MainMenu::addCheckBoxSlots);
    connect(mainMenuViewModel, &MainMenuViewModel::clearCheckBoxSignal, this, &MainMenu::clearCheckBoxSlots);
    connect(mainMenuViewModel, &MainMenuViewModel::addInfoProductSignal, this, &MainMenu::addInfoProductSlots);
    connect(mainMenuViewModel, &MainMenuViewModel::clearLableSignal, this, &MainMenu::clearLableSlots);
    connect(this, &MainMenu::priceFilterChangetSignals, mainMenuViewModel, &MainMenuViewModel::priceFilterChangedSlots);
    connect(ui->tableViewProduct, &QTableView::doubleClicked, mainMenuViewModel, &MainMenuViewModel::selectedElemTableViewSlots);
}

MainMenu::~MainMenu()
{
    delete ui;
}
