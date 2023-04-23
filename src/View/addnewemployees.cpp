#include "addnewemployees.h"
#include "ui_addnewemployees.h"

AddNewEmployees::AddNewEmployees(AddEmployeesViewModel* addEmployeesViewModel, QWidget *parent) :
    addEmployeesViewModel(addEmployeesViewModel),
    QDialog(parent),
    ui(new Ui::AddNewEmployees)
{
    ui->setupUi(this);
    connected();

    addEmployeesViewModel->update();
}

void AddNewEmployees::addItemsToComboBox(const QStringList& first, const QStringList& second)
{
    ui->comboBoxGender->addItems(first);
    ui->comboBoxPosition->addItems(second);
    ui->comboBoxGender->setCurrentIndex(-1);
    ui->comboBoxPosition->setCurrentIndex(-1);
}

void AddNewEmployees::close()
{
    this->close();
}

void AddNewEmployees::connected()
{
    connect(addEmployeesViewModel, &AddEmployeesViewModel::addItemsToComboBox, this, &AddNewEmployees::addItemsToComboBox);
    connect(addEmployeesViewModel, &AddEmployeesViewModel::close, this, &AddNewEmployees::close);
    connect(ui->buttonAddEmployees, &QPushButton::clicked, this, [&]()
    {
//        if(ui->comboBoxGender->currentIndex() == -1 ||ui->comboBoxPosition->currentIndex() == -1)

        addEmployeesViewModel->applyChanges(ui->inputFullName->text(), ui->inputPassword->text(), ui->comboBoxPosition->currentText(), ui->inputPhoneNumber->text(), ui->inputAddress->text(), ui->comboBoxGender->currentText(), ui->dateEdit->date().toString("yyyy.MM.dd"));
    });
}

AddNewEmployees::~AddNewEmployees()
{
    delete ui;
}
