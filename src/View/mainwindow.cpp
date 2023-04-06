//Мои заголовочные файлы формы
#include "mainwindow.h"
#include "mainmenu.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(ConnectionHandler* connectionHandler, QWidget *parent) :
    connectionHandler(connectionHandler),
    thisWindow(nullptr),
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
}

void MainWindow::buttonMainMenu_clicked()
{
    if(qobject_cast<MainMenu*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler->getDB());
    thisViewModel = new MainMenuViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new MainMenu(static_cast<MainMenuViewModel*>(thisViewModel));
    ui->centralwidget->layout()->addWidget(thisWindow);
}

void MainWindow::freeMemory()
{
    if(thisWindow != nullptr && thisViewModel != nullptr && thisModel != nullptr)
    {
        delete thisWindow;
        delete thisViewModel;
        delete thisModel;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
