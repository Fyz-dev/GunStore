//Мои заголовочные файлы формы
#include "mainwindow.h"
#include "addproductdialog.h"
#include "addnewemployees.h"
#include "addnewsupplier.h"
#include "ordering.h"

#include "./ui_mainwindow.h"
#include "qtabbar.h"


MainWindow::MainWindow(MainWindowMediator* mainWindowMediator, QWidget *parent) :
    mainWindowMediator(mainWindowMediator),
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetWindows->tabBar()->hide();
    ui->menuAdminOpen->tabBar()->hide();
    ui->menuAdminOpen->setCurrentIndex(5);

    ui->tableViewProduct->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connected();
    this->mainWindowMediator->settingSignalSlots(this);

    buttonMainMenu_clicked();
}

void MainWindow::modelChangedSlots(QSqlTableModel* modelData)
{
    ui->tableViewProduct->setModel(nullptr);
    ui->tableViewProduct->setModel(modelData);
}

void MainWindow::addCheckBoxSlots(QCheckBox* checkBox, LayoutState& layoutName)
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

void MainWindow::clearCheckBoxSlots()
{
    QLayoutItem *child;
    while ((child = ui->frameCategorys->layout()->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    while ((child = ui->frameCountries->layout()->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    while ((child = ui->frameBrands->layout()->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}

void MainWindow::buttonMainMenu_clicked()
{
    ui->tabWidgetWindows->setCurrentIndex(0);
    windowState = WindowState::MainMenuWindow;
    mainWindowMediator->update(windowState);
}

void MainWindow::connected()
{
    connect(ui->buttonMainMenu, &QPushButton::clicked, this, &MainWindow::buttonMainMenu_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/////////////////////////

void MainWindow::on_buttonAdmin_clicked()
{
    ui->tabWidgetWindows->setCurrentIndex(1);
}

void MainWindow::on_buttonBuyProduct_clicked()
{
    ui->tabWidgetWindows->setCurrentIndex(2);
}

//Оформление заказа
void MainWindow::on_buttonBasket_clicked()
{
    Ordering* FormNewOrdering = new Ordering(this);
    FormNewOrdering->setModal(true);
    FormNewOrdering->exec();
    delete FormNewOrdering;
}

//Меню администратора
void MainWindow::on_buttonAddNewProduct_clicked()
{
    AddProductDialog* FormAddProductDialog = new AddProductDialog(this);
    FormAddProductDialog->setModal(true);
    FormAddProductDialog->exec();
    delete FormAddProductDialog;
}

void MainWindow::on_buttonEditBD_clicked()
{
    ui->menuAdminOpen->setCurrentIndex(0);
}

void MainWindow::on_buttonReportCheck_clicked()
{
    ui->menuAdminOpen->setCurrentIndex(1);
}

void MainWindow::on_buttonInfoEmployees_clicked()
{
    ui->menuAdminOpen->setCurrentIndex(2);
}

void MainWindow::on_buttonAddEmployees_clicked()
{
    AddNewEmployees* FormAddNewEmployees = new AddNewEmployees(this);
    FormAddNewEmployees->setModal(true);
    FormAddNewEmployees->exec();
    delete FormAddNewEmployees;
}

void MainWindow::on_buttonInfoBuyer_clicked()
{
    ui->menuAdminOpen->setCurrentIndex(3);
}

void MainWindow::on_buttonInfoSupplier_clicked()
{
    ui->menuAdminOpen->setCurrentIndex(4);
}

void MainWindow::on_buttonAddSupplier_clicked()
{
    AddNewSupplier* FormAddNewSupplier = new AddNewSupplier(this);
    FormAddNewSupplier->setModal(true);
    FormAddNewSupplier->exec();
    delete FormAddNewSupplier;
}

