#include "menuemployees.h"
#include "ui_menuemployees.h"
#include "elementpeople.h"

MenuEmployees::MenuEmployees(EmployeesModel* employeesModel, QWidget *parent) :
    QWidget(parent),
    employeesModel(employeesModel),
    ui(new Ui::MenuEmployees)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");
    ui->comboBoxIsDelete->addItems({"Наявні співробітники", "Видалені співробітники"});

    update(); 

    connect(ui->buttonAdd, &QPushButton::clicked, this, [&]()
    {
        emit openAddNewEmployees();
    });
}

void MenuEmployees::update()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    for (ElementPeople* item : employeesModel->updateInfoBuyPeople(this))
        layout->insertWidget(layout->count()-1, item);
}

MenuEmployees::~MenuEmployees()
{
    delete ui;
}
