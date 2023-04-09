//Мои заголовочные файлы формы
#include "mainwindow.h"
#include "mainmenu.h"
#include "buyproduct.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(ConnectionHandler* connectionHandler, QWidget *parent) :
    connectionHandler(connectionHandler),
    thisWindow(nullptr),
    thisViewModel(nullptr),
    thisModel(nullptr),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1400, 600);

    connected();
    buttonMainMenu_clicked();
}

void MainWindow::connected()
{
    connect(ui->buttonMainMenu, &QPushButton::clicked, this, &MainWindow::buttonMainMenu_clicked);
    connect(ui->buttonBuyProduct, &QPushButton::clicked, this, &MainWindow::buttonBuyProduct_clicked);
}

void MainWindow::buttonMainMenu_clicked()
{
    if(qobject_cast<MainMenu*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler->getDB());
    thisViewModel = new MainMenuViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new MainMenu(static_cast<MainMenuViewModel*>(thisViewModel), this);
    ui->centralwidget->layout()->addWidget(thisWindow);
}

void MainWindow::buttonBuyProduct_clicked()
{
    if(qobject_cast<BuyProduct*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler->getDB());
    thisViewModel = new BuyProductViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new BuyProduct(static_cast<BuyProductViewModel*>(thisViewModel), this);
    ui->centralwidget->layout()->addWidget(thisWindow);
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
    delete ui;
}
