#include "menuadmin.h"
#include "ui_menuadmin.h"

#include "menueditproduct.h"
#include "productmodel.h"
#include "menueditproductviewmodel.h"
#include "addproductdialog.h"

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
}

void MenuAdmin::openAddNewProductDialog()
{
    std::unique_ptr<ProductModel> productModel = std::make_unique<ProductModel>(connectionHandler->getDB());
    std::unique_ptr<AddProductDialogViewModel> addProductDialogViewModel = std::make_unique<AddProductDialogViewModel>(productModel.get());
    std::unique_ptr<AddProductDialog> addProductDialog = std::make_unique<AddProductDialog>(addProductDialogViewModel.get(), this);
    addProductDialog->exec();
}

void MenuAdmin::buttonEditProduct_clicked()
{
    if(qobject_cast<MenuEditProduct*>(thisWindow))
        return;

    freeMemory();

    thisModel = new ProductModel(connectionHandler->getDB());
    thisViewModel = new MenuEditProductViewModel(static_cast<ProductModel*>(thisModel));
    thisWindow = new MenuEditProduct(static_cast<MenuEditProductViewModel*>(thisViewModel), this);
    ui->widgetForWindowAdmin->layout()->addWidget(thisWindow);
    connect(qobject_cast<MenuEditProduct*>(thisWindow), &MenuEditProduct::openAddNewProductDialogSignals, this, &MenuAdmin::openAddNewProductDialog);
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
