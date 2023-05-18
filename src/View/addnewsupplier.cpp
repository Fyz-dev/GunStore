#include "addnewsupplier.h"
#include "ui_addnewsupplier.h"
#include "formwithbuttonback.h"

#include <QRegularExpressionValidator>

const QRegularExpression AddNewSupplier::regexNumberPhone = QRegularExpression("^0\\d{9}$");
const QRegularExpression AddNewSupplier::regexNull = QRegularExpression("^\\s*$");
const QRegularExpression AddNewSupplier::regexEdrpou = QRegularExpression("^\\d{8}$");
const QRegularExpression AddNewSupplier::regexBank = QRegularExpression("^\\d{16}$");

AddNewSupplier::AddNewSupplier(SupplierModel* supplierModel, QWidget *parent) :
    AddNewSupplier(parent)
{
    this->supplierModel = supplierModel;

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

        if(this->supplierModel->getOneCell(QString("select count(*) from supplier where sup_name = '%1'").arg(ui->inputFullNameSupplier->text())) != "0")
            return notification->show("Такий постачальник вже є!", 2);

        if(this->supplierModel->getOneCell(QString("select count(*) from supplier where sup_edrpou = '%1'").arg(ui->inputEdrpou->text())) != "0")
            return notification->show("Такий ЄДРПОУ вже є!", 2);

        if(this->supplierModel->getOneCell(QString("select count(*) from supplier where sup_bank = '%1'").arg(ui->inpuBank->text())) != "0")
            return notification->show("Такий розрахунковий рахунок вже є!", 2);

        this->supplierModel->requestBD("INSERT INTO supplier(sup_name, sup_edrpou, sup_phoneNum, sup_address, sup_bank) VALUES('" + ui->inputFullNameSupplier->text() + "'," + ui->inputEdrpou->text() + ",'" + ui->inpuNumberPhone->text() + "','" + ui->inpuAddress->text() + "','" + ui->inpuBank->text() + "')");
        FormWithButtonBack::clearStack();
    });
}

AddNewSupplier::AddNewSupplier(const QString& idSupplier, SupplierModel* supplierModel, QWidget* parent) :
    AddNewSupplier(parent)
{
    ui->buttonAddSupplier->hide();
    ui->label->setText("Дані постачальника");

    supplierModel->updateModelViaQuery(QString("select sup_name, sup_edrpou, sup_phoneNum, sup_address, sup_bank from supplier where id_supplier = %1").arg(idSupplier));

    QSqlRelationalTableModel* model = supplierModel->getModelData();

    ui->inputFullNameSupplier->setText(model->index(0, 0).data().toString());
    ui->inputEdrpou->setText(model->index(0, 1).data().toString());
    ui->inpuNumberPhone->setText(model->index(0, 2).data().toString());
    ui->inpuAddress->setText(model->index(0, 3).data().toString());
    ui->inpuBank->setText(model->index(0, 4).data().toString());

    QList<QLineEdit*> list = {ui->inputFullNameSupplier, ui->inputEdrpou, ui->inpuAddress, ui->inpuBank, ui->inpuNumberPhone};

    for (QLineEdit* item : list)
    {
        item->installEventFilter(this);

        connect(item, &QLineEdit::editingFinished, this, [&]()
        {
            if(lastText != qobject_cast<QLineEdit*>(sender())->text())
                ui->buttonChange->show();
        });
    }

    connect(ui->buttonChange, &QPushButton::clicked, this, [=]()
    {
        supplierModel->requestBD(QString("UPDATE supplier SET sup_name = '%1', sup_edrpou = '%2', sup_phoneNum = '%3', sup_address = '%4', sup_bank = '%5' where id_supplier = %6").arg(ui->inputFullNameSupplier->text(), ui->inputEdrpou->text(), ui->inpuNumberPhone->text(), ui->inpuAddress->text(), ui->inpuBank->text(), idSupplier));
        ui->buttonChange->hide();
        notification->show("Зміни внесено до БД!", 2);
    });
}

AddNewSupplier::AddNewSupplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewSupplier)
{
    ui->setupUi(this);
    ui->buttonChange->hide();

    notification = new CenteredNotification;

    ui->inpuNumberPhone->setValidator(new QRegularExpressionValidator(regexNumberPhone));
    ui->inputEdrpou->setValidator(new QRegularExpressionValidator(regexEdrpou));
    ui->inpuBank->setValidator(new QRegularExpressionValidator(regexBank));
}

bool AddNewSupplier::eventFilter(QObject* watched, QEvent* event)
{
    if(QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched))
        if(event->type() == QEvent::FocusIn)
            lastText = lineEdit->text();

    return false;
}

AddNewSupplier::~AddNewSupplier()
{
    delete notification;
    delete ui;
}
