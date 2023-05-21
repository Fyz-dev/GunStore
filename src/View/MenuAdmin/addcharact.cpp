#include "addcharact.h"
#include "ui_addcharact.h"
#include "QTimer"
#include "formwithbuttonback.h"

AddCharact::AddCharact(ProductModel* productModel, QWidget *parent) :
    QWidget(parent),
    productModel(productModel),
    ui(new Ui::AddCharact)
{
    ui->setupUi(this);
    notification = new CenteredNotification;

    QList<QString> listCategory;
    productModel->updateList(listCategory, "select c_name from category");
    ui->comboBoxCategory->addItems(listCategory);

    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->comboBoxCategory, &QComboBox::currentIndexChanged, this, &AddCharact::comboBoxCategoryIndexChanged);
    connect(ui->comboBoxCharact, &QComboBox::currentIndexChanged, this, &AddCharact::comboBoxCharactIndexChanged);
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &AddCharact::valueEnteredTableWidget);
    connect(ui->buttonApply, &QPushButton::clicked, this, &AddCharact::buttonApply_clicked);

    ui->comboBoxCategory->setCurrentIndex(0);
}

void AddCharact::comboBoxCategoryIndexChanged(const int& i)
{
    if(ui->tableWidget->rowCount()>1)
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Увага!");
        msgBox.setText("Усі введені характеристики зникнуть. Ви підтверджуєте це?");

        QPushButton* yes = msgBox.addButton("Так", QMessageBox::ActionRole);
        msgBox.addButton("Ні", QMessageBox::ActionRole);

        msgBox.exec();
        if(msgBox.clickedButton() != yes)
        {
            {ui->comboBoxCategory->blockSignals(true), ui->comboBoxCategory->setCurrentIndex(previousIndexComboBox), ui->comboBoxCategory->blockSignals(false);};
            return;
        }
    }

    ui->comboBoxCharact->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(1);

    QList<QString> listCharact;
    productModel->updateList(this->listCharact, QString("select charact_name from category join categorycharacteristic using(id_category) join characteristic using(id_characteristic) where c_name = '%1'").arg(ui->comboBoxCategory->currentText()));
    productModel->updateList(listCharact, QString("select charact_name from characteristic where charact_name not in(select charact_name from category join categorycharacteristic using(id_category) join characteristic using(id_characteristic) where c_name = '%1')").arg(ui->comboBoxCategory->currentText()));
    ui->comboBoxCharact->addItems(listCharact);
    previousIndexComboBox = i;
}

void AddCharact::comboBoxCharactIndexChanged(const int& i)
{
    if(i == -1)
        return;

    QString currentText = ui->comboBoxCharact->currentText();

    for (int i = 0; i < ui->tableWidget->rowCount()-1; ++i)
        if(ui->tableWidget->item(i, 0)->text() == currentText)
        {
            ui->comboBoxCharact->setCurrentIndex(-1);
            return notification->show("Ця характеристика вже додана!", 2);
        }

    int insertRow = ui->tableWidget->rowCount()-1;
    ui->tableWidget->insertRow(insertRow);
    ui->tableWidget->setItem(insertRow, 0, new QTableWidgetItem(currentText));
    ui->comboBoxCharact->setCurrentIndex(-1);
}

void AddCharact::valueEnteredTableWidget(const int& row, const int& column)
{
    if(row != ui->tableWidget->rowCount()-1 && ui->tableWidget->item(row, column)->data(0).toString().isEmpty())
    {
        QTimer::singleShot(0, this, [=](){ ui->tableWidget->removeRow(row); });
        return;
    }

    QString currentText = ui->tableWidget->item(row, 0)->data(0).toString();
    if(listCharact.contains(currentText))
    {
        ui->tableWidget->item(row, 0)->setText("");
        return notification->show("Така характеристика для категорії вже є!", 2);
    }

    if(row == ui->tableWidget->rowCount()-1)
    {
        if(ui->tableWidget->item(row, 0)->data(0).toString().isEmpty())
            return;

        for (int i = 0; i < ui->tableWidget->rowCount()-1; ++i)
            if(ui->tableWidget->item(i, 0)->text() == currentText)
            {
                ui->tableWidget->item(row, 0)->setText("");
                return notification->show("Ця характеристика вже додана!", 2);
            }

        int insertRow = ui->tableWidget->rowCount();
        ui->tableWidget->blockSignals(true);
        ui->tableWidget->insertRow(insertRow);
        ui->tableWidget->setItem(insertRow, 0, new QTableWidgetItem);
        ui->tableWidget->blockSignals(false);
    }
}

void AddCharact::buttonApply_clicked()
{
    if(ui->tableWidget->rowCount() == 1)
        return notification->show("Додайте характеристики!", 2);

    for (int i = 0; i < ui->tableWidget->rowCount()-1; ++i)
    {
        QString currentText = ui->tableWidget->item(i, 0)->text();
        if(productModel->getOneCell(QString("select count(*) from characteristic where charact_name = '%1'").arg(currentText)) != "0")
        {
            productModel->requestBD(QString("INSERT INTO categorycharacteristic(id_category, id_characteristic) VALUES((select id_category from category where c_name = '%1'), (select id_characteristic from characteristic where charact_name = '%2'))").arg(ui->comboBoxCategory->currentText(), currentText));
        }
        else
        {
            //qDebug() << QString("INSERT INTO characteristic(charact_name) VALUES('%1')").arg(currentText);
            productModel->requestBD(QString("INSERT INTO characteristic(charact_name) VALUES('%1')").arg(currentText));
            productModel->requestBD(QString("INSERT INTO categorycharacteristic(id_category, id_characteristic) VALUES((select id_category from category where c_name = '%1'), %2)").arg(ui->comboBoxCategory->currentText(), QString::number(productModel->getLastInsertId())));
        }
    }

    FormWithButtonBack::clearStack();
}

AddCharact::~AddCharact()
{
    delete notification;
    delete productModel;
    delete ui;
}
