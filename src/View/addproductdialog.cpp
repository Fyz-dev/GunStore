#include "addproductdialog.h"
#include "ui_addproductdialog.h"

#include <QTimer>
#include <QMessageBox>

AddProductDialog::AddProductDialog(AddProductDialogViewModel* addProductDialogViewModel, QWidget *parent) :
    addProductDialogViewModel(addProductDialogViewModel),
    QDialog(parent),
    ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connected();

    addProductDialogViewModel->update();
    ui->comboBox->setCurrentIndex(-1);
}

const QRegularExpression AddProductDialog::regex = QRegularExpression("^\\d+(\\.\\d+)?$");

void AddProductDialog::connected()
{
    connect(ui->inputPrice, &QLineEdit::editingFinished, this, &AddProductDialog::isValidInput);
    connect(ui->inputWeight, &QLineEdit::editingFinished, this, &AddProductDialog::isValidInput);
    connect(addProductDialogViewModel, &AddProductDialogViewModel::updateComboBoxSignals, this, &AddProductDialog::updateComboBoxSlots);
    connect(addProductDialogViewModel, &AddProductDialogViewModel::setComboBoxSignals, this, &AddProductDialog::setComboBoxSlots);
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &AddProductDialog::valueEnteredTableWidget);
    connect(this, &AddProductDialog::selectedItemComboBox, addProductDialogViewModel, &AddProductDialogViewModel::selectedItemComboBox);
    connect(this, &AddProductDialog::addNewProduct, addProductDialogViewModel, &AddProductDialogViewModel::addNewProduct);

    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, [&](const int& i)
    {
        if((ui->tableWidget->rowCount() > 1))
        {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Увага!");
            msgBox.setText("Усі введені дані про характеристики зникнуть. Ви підтверджуєте це?");

            QPushButton* yes = msgBox.addButton("Так", QMessageBox::ActionRole);
            msgBox.addButton("Ні", QMessageBox::ActionRole);

            msgBox.exec();
            if(msgBox.clickedButton() != yes)
            {
                ui->comboBox->blockSignals(true), ui->comboBox->setCurrentIndex(previousIndexComboBox), ui->comboBox->blockSignals(false);
                return;
            }
        }

        previousIndexComboBox = i;
        emit selectedItemComboBox(i, qobject_cast<QComboBox*>(sender()));
    });

    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, [&](const int& row, const int& column)
    {
        if(column == 1)
            ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
        else
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });

    connect(ui->buttonAdd, &QPushButton::clicked, this, [&]()
    {
        emit addNewProduct(ui->inputName->text(), QString::number(ui->inputPrice->text().toDouble(), 'f', 2), ui->inputBrand->text(),
        QString::number(ui->inputWeight->text().toDouble(), 'f', 2), ui->inputPackage->text(), ui->inputCountry->text(), ui->comboBox->currentText(), ui->tableWidget);
        this->close();
    });
}

void AddProductDialog::valueEnteredTableWidget(const int& row, const int& column)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0));

    if(ui->tableWidget->item(row, column)->data(0).toString().isEmpty() && row+1 != ui->tableWidget->rowCount())
    {
        QTimer::singleShot(0, this, [=](){
            ui->tableWidget->removeRow(row);
        });
        return comboBox->addItem(ui->tableWidget->item(row, 0)->data(0).toString());
    }

    if(row+1 != ui->tableWidget->rowCount() || ui->tableWidget->item(row, column)->data(0).toString() == "" || comboBox->count() == 0)
        return;

    ui->tableWidget->blockSignals(true);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount()-1);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(comboBox->currentText()));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(ui->tableWidget->item(row+1, 1)->text()));
    ui->tableWidget->item(row+1, 1)->setText("");
    ui->tableWidget->blockSignals(false);

    comboBox->removeItem(comboBox->currentIndex());
}

void AddProductDialog::isValidInput()
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
    if(!regex.match(lineEdit->text()).hasMatch())
        lineEdit->setText("");
}

void AddProductDialog::updateComboBoxSlots(const QString& text)
{
    ui->comboBox->blockSignals(true);
    ui->comboBox->addItem(text);
    ui->comboBox->blockSignals(false);
}

void AddProductDialog::setComboBoxSlots(QComboBox* comboBox)
{
    ui->comboBox->blockSignals(true);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->clearContents();
    ui->tableWidget->setCellWidget(0, 0, comboBox);
    ui->comboBox->blockSignals(false);
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}
