#include "elementcharacteristic.h"
#include "ui_elementcharacteristic.h"

ElementCharacteristic::ElementCharacteristic(const QString& nameCharact, const QString& valueCharact, const int& idProductValue, bool lineEditIsReadOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementCharacteristic)
{
    ui->setupUi(this);
    ui->nameCharacteristic->setText(nameCharact + ":");
    ui->nameCharacteristic->setAlignment(Qt::AlignLeft);

    ui->valueCharacteristic->setText(valueCharact);
    ui->valueCharacteristic->setReadOnly(lineEditIsReadOnly);

    this->idProductValue = idProductValue;

    connect(ui->valueCharacteristic, &QLineEdit::editingFinished, this, [&]()
    {
        emit changedValueSignals(this);
    });
}

const QString ElementCharacteristic::getValue() const { return ui->valueCharacteristic->text(); }

ElementCharacteristic::~ElementCharacteristic()
{
    delete ui;
}
