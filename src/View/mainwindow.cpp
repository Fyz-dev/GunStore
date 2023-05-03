#include "mainwindow.h"
#include "mainmenu.h"
#include "buyproduct.h"
#include "menuadmin.h"
#include "ordering.h"
#include "formforempty.h"
#include "./ui_mainwindow.h"

//Основной класс где происходит контроль таких окон как: Главное окно, закупки, админа, оформление заказа
//При желание добавить новое окно в область видимости основного окна НЕОБХОДИМО вызвать метод freeMemory()

MainWindow::MainWindow(ConnectionHandler* connectionHandler, QWidget *parent) :
    connectionHandler(connectionHandler),
    thisWindow(nullptr),
    thisViewModel(nullptr),
    thisModel(nullptr),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    formWithButtonBack = FormWithButtonBack::getInstance(ui->centralwidget->layout());

    this->resize(1400, 600);

    connected();

    buttonMainMenu_clicked();
    colorButtonControl(ui->buttonMainMenu);
}

void MainWindow::connected()
{
    connect(ui->buttonMainMenu, &QPushButton::clicked, this, &MainWindow::buttonMainMenu_clicked);
    connect(ui->buttonBuyProduct, &QPushButton::clicked, this, &MainWindow::buttonBuyProduct_clicked);
    connect(ui->buttonAdmin, &QPushButton::clicked, this, &MainWindow::buttonAdmin_clicked);
    connect(ui->buttonBasket, &QPushButton::clicked, this, &MainWindow::buttonBasket_clicked);
}

void MainWindow::buttonMainMenu_clicked()
{
    if(qobject_cast<MainMenu*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler);
    thisViewModel = new MainMenuViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new MainMenu(static_cast<MainMenuViewModel*>(thisViewModel), this);
    ui->centralwidget->layout()->addWidget(thisWindow);

    connect(static_cast<MainMenu*>(thisWindow), &MainMenu::updateCountForProduct, this, [&](const int& newCount)
    {
        ui->printCountProduct->setText(QString::number(newCount));
    });
    ui->printCountProduct->setText("0");

    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::buttonBuyProduct_clicked()
{
    if(qobject_cast<BuyProduct*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler);
    thisViewModel = new BuyProductViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new BuyProduct(static_cast<BuyProductViewModel*>(thisViewModel), this);
    ui->centralwidget->layout()->addWidget(thisWindow);
    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::buttonAdmin_clicked()
{
    if(qobject_cast<MenuAdmin*>(thisWindow))
        return;

    freeMemory();

    thisModel = nullptr;
    thisViewModel = nullptr;
    thisWindow = new MenuAdmin(connectionHandler, this);
    ui->centralwidget->layout()->addWidget(thisWindow);
    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::buttonBasket_clicked()
{
    if(dynamic_cast<MainMenuViewModel*>(thisViewModel)->getListProduct().isEmpty())
        FormWithButtonBack::pushToView({new FormForEmpty});
    else
        FormWithButtonBack::pushToView({new Ordering(static_cast<MainMenuViewModel*>(thisViewModel)->getListProduct(), connectionHandler, this)});
}

void MainWindow::colorButtonControl(QPushButton* sender)
{
    if(sender)
    {
        if (thisButton)
            thisButton->setStyleSheet("QPushButton{ background-color: transparent; } QPushButton::hover {background-color: #02cc88;}");

        sender->setStyleSheet("QPushButton{ background-color: #16171b; }");
        thisButton = sender;

        ui->buttonBasket->setVisible(sender == ui->buttonMainMenu);
        ui->printCountProduct->setVisible(sender == ui->buttonMainMenu);
    }
}

//Очищаем память
void MainWindow::freeMemory()
{
    if(thisWindow)
    {
        delete thisWindow;
        thisWindow = nullptr;
    }

    if(thisViewModel)
    {
        delete thisViewModel;
        thisViewModel = nullptr;
    }

    if(thisModel)
    {
        delete thisModel;
        thisModel = nullptr;
    }
}

MainWindow::~MainWindow()
{
    freeMemory();

    delete formWithButtonBack;
    delete ui;
}
