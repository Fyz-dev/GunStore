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

    connect(ui->comboBoxIsDelete, &QComboBox::currentIndexChanged, this, [&](const int& i)
    {
        update();
    });
}

void MenuEmployees::update()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    for (ElementPeople* item : employeesModel->updateInfoBuyPeople(this, QString::number(ui->comboBoxIsDelete->currentIndex())))
        layout->insertWidget(layout->count()-1, item);
}

void MenuEmployees::show()
{
    update();
    QWidget::show();
}

void MenuEmployees::hide()
{
    QWidget::hide();
}

void MenuEmployees::search(const QString& text)
{
    for (ElementPeople* item : employeesModel->getList())
        if(!item->getTitle().contains(text, Qt::CaseInsensitive))
            item->hide();
        else
            item->show();
}

MenuEmployees::~MenuEmployees()
{
    delete ui;
}
