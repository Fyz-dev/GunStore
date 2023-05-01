#include "addbuyer.h"
#include "ui_addbuyer.h"
#include "formwithbuttonback.h"

#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QDateTime>

AddBuyer::AddBuyer(ProductModel* productModel, QHash<int, int>& listProduct, QWidget *parent) :
    QWidget(parent),
    productModel(productModel),
    listProduct(listProduct),
    ui(new Ui::AddBuyer)
{
    ui->setupUi(this);

    QStringList list;
    productModel->updateList(list, "select full_name from buyer");

    ui->inputFIO->addItems(list);
    ui->inputFIO->setEditable(true);
    ui->inputFIO->setInsertPolicy(QComboBox::NoInsert);
    ui->inputFIO->setCurrentIndex(-1);

    connected();
}

void AddBuyer::connected()
{
    connect(ui->buttonOrder, &QPushButton::clicked, this, &AddBuyer::buttonOrder_clicked);
    connect(ui->inputFIO, &QComboBox::currentIndexChanged, this, &AddBuyer::comboBoxIndexChanged);

    //Фильтр текста
    QLineEdit* lineEdtiComboBox = ui->inputFIO->lineEdit();
    connect(lineEdtiComboBox, &QLineEdit::textChanged, this, [=](const QString &text){
        QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(lineEdtiComboBox);
        if (proxyModel)
            proxyModel->setFilterRegularExpression(QRegularExpression(QString("")));
    });

    connect(lineEdtiComboBox, &QLineEdit::editingFinished, this, &AddBuyer::inputNewFIO);
}

void AddBuyer::buttonOrder_clicked()
{
    productModel->requestBD(QString("INSERT INTO sales(inn, id_worker, date_time) VALUES(%1, %2, NOW())").arg(ui->inputINN->text(), productModel->getIdWorker()));
    int idSales = productModel->getLastInsertId();

    for (QHash<int, int>::const_iterator i = listProduct.constBegin(); i != listProduct.constEnd(); ++i)
    {
        productModel->requestBD(QString("INSERT INTO listproduct(id_sales, id_product, listP_count) VALUES(%1, %2, %3)").arg(QString::number(idSales), QString::number(i.key()), QString::number(i.value())));
        productModel->requestBD(QString("UPDATE product SET p_count = p_count - %1 WHERE id_product = %2").arg(QString::number(i.value()), QString::number(i.key())));
    }

    FormWithButtonBack::clearStack();
}

void AddBuyer::comboBoxIndexChanged(const int& i)
{
    productModel->updateModelViaQuery(QString("select inn, phone_number, email, city, details from buyer join address using(id_address) where full_name = '%1'").arg(ui->inputFIO->currentText()));
    QSqlRelationalTableModel* model = productModel->getModelData();

    ui->inputINN->setText(model->index(0, 0).data().toString());
    ui->inputPhone->setText(model->index(0, 1).data().toString());
    ui->inputEmail->setText(model->index(0, 2).data().toString());
    ui->inputCity->setText(model->index(0, 3).data().toString());
    ui->inputAddressDetails->setText(model->index(0, 4).data().toString());
    setEditable(false);
}

void AddBuyer::inputNewFIO()
{
    QComboBox* comboBox = ui->inputFIO;
    for (int i = 0; i < comboBox->count(); ++i)
        if(comboBox->itemText(i) == ui->inputFIO->currentText())
            return;

    QString temp = ui->inputFIO->currentText();
    ui->inputFIO->blockSignals(true);
    ui->inputFIO->setCurrentIndex(-1);
    ui->inputFIO->blockSignals(false);

    ui->inputFIO->setCurrentText(temp);

    setEditable(true);
    ui->inputINN->clear();
    ui->inputPhone->clear();
    ui->inputEmail->clear();
    ui->inputCity->clear();
    ui->inputAddressDetails->clear();
}

void AddBuyer::setEditable(bool isEdit)
{
    for (int i = 0; i < ui->verticalLayout_8->count(); ++i)
        if(QLayout* layout = dynamic_cast<QLayout*>(ui->verticalLayout_8->itemAt(i)))
            for (int index = 0; index < layout->count(); ++index)
                if(QLineEdit* lineEdit = qobject_cast<QLineEdit*>(layout->itemAt(index)->widget()))
                    lineEdit->setReadOnly(!isEdit);
}

AddBuyer::~AddBuyer()
{
    delete ui;
}
