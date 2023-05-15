#include "addbuyer.h"
#include "ui_addbuyer.h"
#include "formwithbuttonback.h"
#include "printer.h"

#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QDateTime>
#include <QSqlError>

QRegularExpression AddBuyer::regexNumberPhone = QRegularExpression("^0\\d{9}$");
QRegularExpression AddBuyer::regexINN= QRegularExpression("^\\d{10}$");
QRegularExpression AddBuyer::regexEmail = QRegularExpression("^[\\w.-]+@[a-zA-Z_-]+?\\.[a-zA-Z]{2,}$");
QRegularExpression AddBuyer::regexLicense= QRegularExpression("^\\d{7}$");


AddBuyer::AddBuyer(ProductModel* productModel, QHash<int, int>& listProduct, QWidget *parent) :
    AddBuyer(parent)
{
    this->productModel = productModel;
    this->listProduct = &listProduct;

    QStringList list;
    productModel->updateList(list, "select full_name from buyer");

    ui->inputFIO->addItems(list);
    ui->inputFIO->setEditable(true);
    ui->inputFIO->setInsertPolicy(QComboBox::NoInsert);
    ui->inputFIO->setCurrentIndex(-1);

    ui->inputPhone->setValidator(new QRegularExpressionValidator(regexNumberPhone));
    ui->inputINN->setValidator(new QRegularExpressionValidator(regexINN));
    ui->inputEmail->setValidator(new QRegularExpressionValidator(regexEmail));
    ui->inputLicense->setValidator(new QRegularExpressionValidator(regexLicense));

    connected();
}

AddBuyer::AddBuyer(const QString& FIO, const QString& INN, const QString& numberPhone, const QString& email, const QString& city, const QString& details, const QString& license, QWidget *parent) :
    AddBuyer(parent)
{
    QLineEdit* fio = new QLineEdit(this);
    fio->setReadOnly(true);
    setEditable(false);

    ui->inputFIO->hide();
    ui->buttonOrder->hide();
    ui->verticalLayout->addWidget(fio);

    fio->setText(FIO);
    ui->inputINN->setText(INN);
    ui->inputPhone->setText(numberPhone);
    ui->inputEmail->setText(email);
    ui->inputCity->setText(city);
    ui->inputAddressDetails->setText(details);
    ui->inputLicense->setText(license);
}

AddBuyer::AddBuyer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBuyer)
{
    ui->setupUi(this);
    notification = new CenteredNotification;
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
    QString INN = ui->inputINN->text();
    QString FIO = ui->inputFIO->lineEdit()->text();
    QString phoneNumber = ui->inputPhone->text();
    QString email = ui->inputEmail->text();
    QString city = ui->inputCity->text();
    QString detailsAddress = ui->inputAddressDetails->text();
    QString license = ui->inputLicense->text();

    if(!regexINN.match(INN).hasMatch())
        return notification->show("Введіть коректний ІНН!", 2);

    if(!regexNumberPhone.match(phoneNumber).hasMatch())
        return notification->show("Введіть коректний номер телефону!", 2);

    if(!regexEmail.match(email).hasMatch())
        return notification->show("Введіть коректну електронну пошту!", 2);

    if(!regexLicense.match(license).hasMatch())
        return notification->show("Введіть коректну ліцензію!", 2);

    if(ui->inputFIO->currentIndex() == -1)
    {
        if(productModel->getOneCell(QString("SELECT COUNT(*) FROM buyer WHERE inn = %1").arg(INN)) != "0")
            return notification->show("Такий покупець вже є!", 2);

        productModel->requestBD(QString("INSERT INTO address(city, details) VALUES('%1', '%2')").arg(city, detailsAddress));
        productModel->requestBD(QString("INSERT INTO buyer(inn, full_name, phone_number, email, id_address, license) VALUES('%1', '%2', '%3', '%4', %5, %6)")
                                .arg(INN, FIO, phoneNumber, email, QString::number(productModel->getLastInsertId()), license));
    }

    //Оформление заказа
    productModel->requestBD(QString("INSERT INTO sales(inn, id_worker, date_time) VALUES(%1, %2, NOW())").arg(INN, productModel->getIdWorker()));
    int idSales = productModel->getLastInsertId();

    for (QHash<int, int>::const_iterator i = listProduct->constBegin(); i != listProduct->constEnd(); ++i)
    {
        productModel->requestBD(QString("INSERT INTO listproduct(id_sales, id_product, listP_count) VALUES(%1, %2, %3)").arg(QString::number(idSales), QString::number(i.key()), QString::number(i.value())));
        productModel->requestBD(QString("UPDATE product SET p_count = p_count - %1 WHERE id_product = %2").arg(QString::number(i.value()), QString::number(i.key())));
    }

    Printer printer(QPageSize::B7);
    printer.printCheque(*listProduct, productModel, productModel->getOneCell(QString("select date_time from sales where id_sales = %1").arg(QString::number(idSales))));

    listProduct->clear();
    FormWithButtonBack::clearStack();
}

void AddBuyer::comboBoxIndexChanged(const int& i)
{
    productModel->updateModelViaQuery(QString("select inn, phone_number, email, city, details, license from buyer join address using(id_address) where full_name = '%1'").arg(ui->inputFIO->currentText()));
    QSqlRelationalTableModel* model = productModel->getModelData();

    ui->inputINN->setText(model->index(0, 0).data().toString());
    ui->inputPhone->setText(model->index(0, 1).data().toString());
    ui->inputEmail->setText(model->index(0, 2).data().toString());
    ui->inputCity->setText(model->index(0, 3).data().toString());
    ui->inputAddressDetails->setText(model->index(0, 4).data().toString());
    ui->inputLicense->setText(model->index(0, 5).data().toString());
    setEditable(false);
}

void AddBuyer::inputNewFIO()
{
    if(ui->inputFIO->currentIndex() == -1)
        return;

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
    ui->inputLicense->clear();
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
    delete notification;
    delete ui;
}
