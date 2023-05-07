#include "addnewsupplier.h"
#include "ui_addnewsupplier.h"
#include "formwithbuttonback.h"

#include <QRegularExpressionValidator>

const QRegularExpression AddNewSupplier::regexNumberPhone = QRegularExpression("^0\\d{9}$");
const QRegularExpression AddNewSupplier::regexNull = QRegularExpression("^\\s*$");
const QRegularExpression AddNewSupplier::regexEdrpou = QRegularExpression("^\\d{8}$");
const QRegularExpression AddNewSupplier::regexBank = QRegularExpression("^\\d{16}$");

AddNewSupplier::AddNewSupplier(SupplierModel* supplierModel, QWidget *parent) :
    supplierModel(supplierModel),
    QDialog(parent),
    ui(new Ui::AddNewSupplier)
{
    ui->setupUi(this);
    notification = new CenteredNotification;

    ui->inpuNumberPhone->setValidator(new QRegularExpressionValidator(regexNumberPhone));
    ui->inputEdrpou->setValidator(new QRegularExpressionValidator(regexEdrpou));
    ui->inpuBank->setValidator(new QRegularExpressionValidator(regexBank));

    connect(ui->buttonAddSupplier, &QPushButton::clicked, this, [&]()
    {
        QList<QLineEdit*> list = {ui->inputFullNameSupplier, ui->inputEdrpou, ui->inpuAddress, ui->inpuBank, ui->inpuNumberPhone};

        for (QLineEdit* item : list)
            if(regexNull.match(item->text()).hasMatch())
                return notification->show("Заповніть усі ключові поля!", 2);

        if (!regexEdrpou.match(ui->inputEdrpou->text()).hasMatch())
            return notification->show("Введіть коректний ЄДРПОУ!", 2);

        if (!regexNumberPhone.match(ui->inpuNumberPhone->text()).hasMatch())
            return notification->show("Введіть коректний номер телефону!", 2);

        if (!regexBank.match(ui->inpuBank->text()).hasMatch())
            return notification->show("Введіть коректний розрахунковий рахунок!", 2);

        this->supplierModel->requestBD("INSERT INTO supplier(sup_name, sup_edrpou, sup_phoneNum, sup_address, sup_bank) VALUES('" + ui->inputFullNameSupplier->text() + "'," + ui->inputEdrpou->text() + ",'" + ui->inpuNumberPhone->text() + "','" + ui->inpuAddress->text() + "','" + ui->inpuBank->text() + "')");
        FormWithButtonBack::clearStack();
    });
}

AddNewSupplier::~AddNewSupplier()
{
    delete notification;
    delete ui;
}
