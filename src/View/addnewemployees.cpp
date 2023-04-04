#include "addnewemployees.h"
#include "ui_addnewemployees.h"

AddNewEmployees::AddNewEmployees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewEmployees)
{
    ui->setupUi(this);
}

AddNewEmployees::~AddNewEmployees()
{
    delete ui;
}
