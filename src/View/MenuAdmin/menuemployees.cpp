#include "menuemployees.h"
#include "ui_menuemployees.h"

MenuEmployees::MenuEmployees(MenuEmployeesViewModel* menuEmployeesViewModel, QWidget *parent) :
    menuEmployeesViewModel(menuEmployeesViewModel),
    QWidget(parent),
    ui(new Ui::MenuEmployees)
{
    ui->setupUi(this);
    ui->tableViewWorker->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connected();

    menuEmployeesViewModel->update();
    ui->tableViewWorker->setItemDelegate(menuEmployeesViewModel->getDelegate());
}

void MenuEmployees::buttonAddEmployees_clicked()
{
    emit openAddNewEmployees();
    menuEmployeesViewModel->update();
}

void MenuEmployees::connected()
{
    connect(menuEmployeesViewModel, &MenuEmployeesViewModel::modelChangedSignals, this, &MenuEmployees::modelChangedSlots);
    connect(ui->buttonAddEmployees, &QPushButton::clicked, this, &MenuEmployees::buttonAddEmployees_clicked);
    connect(ui->buttonApplyChanges, &QPushButton::clicked, this, [&]()
    {
        menuEmployeesViewModel->applyChanges();
        menuEmployeesViewModel->update();
    });

    connect(ui->buttonDeleteEmployees, &QPushButton::clicked, this, [&]()
    {
        if(ui->tableViewWorker->currentIndex().isValid())
        {
            menuEmployeesViewModel->addToRemove(ui->tableViewWorker->currentIndex().row());
            ui->tableViewWorker->update();
        }
    });
}

void MenuEmployees::modelChangedSlots(QAbstractTableModel* modelData)
{
    ui->tableViewWorker->setModel(nullptr);
    ui->tableViewWorker->setModel(modelData);
    ui->tableViewWorker->hideColumn(0);
}

MenuEmployees::~MenuEmployees()
{
    delete ui;
}
