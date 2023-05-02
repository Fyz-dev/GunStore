#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(MainMenuViewModel* mainMenuViewModel, QWidget *parent) :
    mainMenuViewModel(mainMenuViewModel),
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    connected();    
    mainMenuViewModel->update();    

    ui->tableViewProduct->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewProduct->hideColumn(0);

    notification = new CenteredNotification;
}

void MainMenu::modelChangedSlots(QAbstractTableModel * modelData)
{
    ui->tableViewProduct->setModel(nullptr);
    ui->tableViewProduct->setModel(modelData);
    ui->tableViewProduct->setItemDelegate(mainMenuViewModel->getDelegate());
}

void MainMenu::addCheckBoxSlots(QCheckBox* checkBox, const LayoutState& layoutName)
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

void MainMenu::addInfoProductSlots(QWidget* widget)
{
    if(widget == nullptr)
    {
        ui->verticalLayout_4->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        return;
    }

    ui->infoSelectProduct->layout()->addWidget(widget);
}

void MainMenu::clearCheckBoxSlots()
{
    deleteWidget(ui->frameCategorys->layout());
    deleteWidget(ui->frameCountries->layout());
    deleteWidget(ui->frameBrands->layout());
}

void MainMenu::priceFilterChangedSlots()
{
    emit priceFilterChangedSignals(ui->inputTo, ui->inputDo);
}

void MainMenu::clearLableSlots()
{
    ui->tableViewProduct->hideColumn(0);
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

void MainMenu::buttonAddOrder_clicked()
{
    if(!ui->tableViewProduct->currentIndex().isValid())
        return notification->show("Виберіть товар!", 2);

    if (mainMenuViewModel->changedListProductForSale(ui->tableViewProduct->currentIndex().row(), ui->inputCountProduct->text().toInt()))
    {
        emit updateCountForProduct(mainMenuViewModel->getListProductForSale().count());
        ui->tableViewProduct->update();
    }

    ui->inputCountProduct->setText("1");
}

void MainMenu::show()
{
    mainMenuViewModel->syncHashAndList();
    emit updateCountForProduct(mainMenuViewModel->getListProductForSale().count());
    QWidget::show();
}

void MainMenu::hide()
{
    notification->close();
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
    connect(this, &MainMenu::priceFilterChangedSignals, mainMenuViewModel, &MainMenuViewModel::priceFilterChangedSlots);
    connect(ui->buttonAddOrder, &QPushButton::clicked, this, &MainMenu::buttonAddOrder_clicked);
    connect(ui->tableViewProduct, &QTableView::clicked, this, [&](const QModelIndex& i)
    {
        mainMenuViewModel->selectedElemTableViewSlots(i);
    });


    connect(ui->inputCountProduct, &QLineEdit::editingFinished, this, [&]()
    {
        static QRegularExpression reg("^[1-9]\\d*$");
        if(!reg.match(ui->inputCountProduct->text()).hasMatch() || ui->inputCountProduct->text().isEmpty())
        {
            ui->inputCountProduct->setText("1");
            return notification->show("Введіть коректну кількість!", 2);
        }
    });
}

MainMenu::~MainMenu()
{
    delete notification;
    delete ui;
}
