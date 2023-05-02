#include "menuadmin.h"
#include "ui_menuadmin.h"

#include "menueditproduct.h"
#include "productmodel.h"
#include "menueditproductviewmodel.h"
#include "addproductdialog.h"
#include "menuemployees.h"
#include "employeesmodel.h"
#include "menuemployeesviewmodel.h"
#include "addnewemployees.h"
#include "addemployeesviewmodel.h"
#include "suppliermodel.h"
#include "menusupplierviewmodel.h"
#include "menusupplier.h"
#include "addnewsupplier.h"
#include "formwithbuttonback.h"

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
}

void MenuAdmin::openAddNewProductDialog()
{
    ProductModel* productModel = new ProductModel(connectionHandler);
    AddProductDialogViewModel* addProductDialogViewModel = new AddProductDialogViewModel(productModel);
    FormWithButtonBack::pushToView({new AddProductDialog(addProductDialogViewModel, this)});
}

void MenuAdmin::openAddNewEmployees()
{
    std::unique_ptr<EmployeesModel> employeesModel = std::make_unique<EmployeesModel>(connectionHandler);
    std::unique_ptr<AddEmployeesViewModel> addEmployeesViewModel = std::make_unique<AddEmployeesViewModel>(employeesModel.get());
    std::unique_ptr<AddNewEmployees> addNewEmployees = std::make_unique<AddNewEmployees>(addEmployeesViewModel.get(), this);

    addNewEmployees->exec();
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
}

void MenuAdmin::buttonInfoEmployees_clicked()
{
    if(qobject_cast<MenuEmployees*>(thisWindow))
        return;

    freeMemory();

    thisModel = new EmployeesModel(connectionHandler);
    thisViewModel = new MenuEmployeesViewModel(static_cast<EmployeesModel*>(thisModel));
    thisWindow = new MenuEmployees(static_cast<MenuEmployeesViewModel*>(thisViewModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    connect(qobject_cast<MenuEmployees*>(thisWindow), &MenuEmployees::openAddNewEmployees, this, &MenuAdmin::openAddNewEmployees);
}

void MenuAdmin::buttonInfoSupplier_clicked()
{
    if(qobject_cast<MenuSupplier*>(thisWindow))
        return;

    freeMemory();

    thisModel = new SupplierModel(connectionHandler);
    thisViewModel = new MenuSupplierViewModel(static_cast<SupplierModel*>(thisModel));
    thisWindow = new MenuSupplier(static_cast<MenuSupplierViewModel*>(thisViewModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    connect(qobject_cast<MenuSupplier*>(thisWindow), &MenuSupplier::openAddSupplier, this, &MenuAdmin::openAddSupplier);
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
