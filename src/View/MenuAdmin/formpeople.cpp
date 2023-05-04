#include "formpeople.h"
#include "ui_formpeople.h"

FormPeople::FormPeople(const QString& INN, const QString& FIO, BaseModel* model, QWidget *parent) :
    QWidget(parent),
    model(model),
    ui(new Ui::FormPeople)
{
    ui->setupUi(this);

    ui->labelTop->setText(FIO);
    ui->labelTopBottom->setText("ІНН:" + INN);
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");
}

void FormPeople::update()
{

}

FormPeople::~FormPeople()
{
    delete model;
    delete ui;
}
