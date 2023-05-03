#include "formforempty.h"
#include "ui_formforempty.h"

FormForEmpty::FormForEmpty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForEmpty)
{
    ui->setupUi(this);
    ui->label_2->setStyleSheet("font: 16pt \"Franklin Gothic Medium\"; color: #818381;");
}

FormForEmpty::~FormForEmpty()
{
    delete ui;
}
