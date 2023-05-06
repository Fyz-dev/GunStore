#include "menuadmin.h"
#include "ui_menuadmin.h"

#include "menueditproduct.h"
#include "productmodel.h"
#include "menueditproductviewmodel.h"
#include "addproductdialog.h"
#include "menuemployees.h"
#include "employeesmodel.h"
#include "addnewemployees.h"
#include "addemployeesviewmodel.h"
#include "suppliermodel.h"
#include "menusupplier.h"
#include "addnewsupplier.h"
#include "formwithbuttonback.h"
#include "menubuyer.h"
#include "buyermodel.h"

//Класс где происходит контроль всех окон админа
//При желание добавить новое окно в область видимости окна администратора НЕОБХОДИМО вызвать метод freeMemory()

MenuAdmin::MenuAdmin(ConnectionHandler* connectionHandler, QWidget *parent) :
    connectionHandler(connectionHandler),
    thisWindow(nullptr),
    thisViewModel(nullptr),
    thisModel(nullptr),
    QWidget(parent),
    ui(new Ui::MenuAdmin)
{
    ui->setupUi(this);
    connected();
}

void MenuAdmin::connected()
{
    connect(ui->buttonEditProduct, &QPushButton::clicked, this, &MenuAdmin::buttonEditProduct_clicked);
    connect(ui->buttonInfoEmployees, &QPushButton::clicked, this, &MenuAdmin::buttonInfoEmployees_clicked);
    connect(ui->buttonInfoSupplier, &QPushButton::clicked, this, &MenuAdmin::buttonInfoSupplier_clicked);
    connect(ui->buttonInfoBuyer, &QPushButton::clicked, this, &MenuAdmin::buttonInfoBuyer_clicked);
}

void MenuAdmin::openAddNewProductDialog()
{
    ProductModel* productModel = new ProductModel(connectionHandler);
    AddProductDialogViewModel* addProductDialogViewModel = new AddProductDialogViewModel(productModel);
    FormWithButtonBack::pushToView({new AddProductDialog(addProductDialogViewModel, this)});
}

void MenuAdmin::openAddNewEmployees()
{
    EmployeesModel* employeesModel = new EmployeesModel(connectionHandler);
    AddEmployeesViewModel* addEmployeesViewModel = new AddEmployeesViewModel(employeesModel);
    FormWithButtonBack::pushToView({new AddNewEmployees(addEmployeesViewModel, this)});
}

void MenuAdmin::openAddSupplier()
{
    std::unique_ptr<SupplierModel> supplierModel = std::make_unique<SupplierModel>(connectionHandler);
    std::unique_ptr<AddNewSupplier> addNewSupplier = std::make_unique<AddNewSupplier>(supplierModel.get(), this);
    addNewSupplier->exec();
}

void MenuAdmin::buttonEditProduct_clicked()
{
    if(qobject_cast<MenuEditProduct*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler);
    thisViewModel = new MenuEditProductViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new MenuEditProduct(static_cast<MenuEditProductViewModel*>(thisViewModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    connect(qobject_cast<MenuEditProduct*>(thisWindow), &MenuEditProduct::openAddNewProductDialogSignals, this, &MenuAdmin::openAddNewProductDialog);
    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MenuAdmin::buttonInfoEmployees_clicked()
{
    if(qobject_cast<MenuEmployees*>(thisWindow))
        return;

    freeMemory();

    thisModel = new EmployeesModel(connectionHandler);
    thisViewModel = nullptr;
    thisWindow = new MenuEmployees(static_cast<EmployeesModel*>(thisModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    connect(qobject_cast<MenuEmployees*>(thisWindow), &MenuEmployees::openAddNewEmployees, this, &MenuAdmin::openAddNewEmployees);
    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MenuAdmin::buttonInfoSupplier_clicked()
{
    if(qobject_cast<MenuSupplier*>(thisWindow))
        return;

    freeMemory();

    thisModel = new SupplierModel(connectionHandler);
    thisWindow = new MenuSupplier(static_cast<SupplierModel*>(thisModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MenuAdmin::buttonInfoBuyer_clicked()
{
    if(qobject_cast<MenuBuyer*>(thisWindow))
        return;

    freeMemory();

    thisModel = new BuyerModel(connectionHandler);
    thisViewModel = nullptr;
    thisWindow = new MenuBuyer(static_cast<BuyerModel*>(thisModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    colorButtonControl(qobject_cast<QPushButton*>(sender()));
}

void MenuAdmin::show()
{
    if(IView* view = dynamic_cast<IView*>(thisWindow))
        view->show();

    QWidget::show();
}

void MenuAdmin::hide()
{
    QWidget::hide();
}

void MenuAdmin::colorButtonControl(QPushButton* sender)
{
    if(!sender)
        return;

    if(thisButton)
        thisButton->setStyleSheet("QWidget#frameButtonCheckInfo QPushButton{ background-color: transparent; }"
                                  " QWidget#frameButtonCheckInfo QPushButton::hover{ border-radius: 5px; background-color: rgba(255, 255, 255, 30); padding-left: 15px; }");

    thisButton = sender;
    sender->setStyleSheet("QWidget#frameButtonCheckInfo QPushButton{ margin-left: 11px; background-color: rgba(1, 176, 117, 200); }"
                          "QWidget#frameButtonCheckInfo QPushButton::hover{padding-left:4px;}");
}

void MenuAdmin::freeMemory()
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

MenuAdmin::~MenuAdmin()
{
    freeMemory();
    delete ui;
}
