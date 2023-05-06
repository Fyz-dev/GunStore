#include "addnewemployees.h"
#include "ui_addnewemployees.h"
#include "formwithbuttonback.h"

const QRegularExpression AddNewEmployees::regexNumberPhone = QRegularExpression("^0\\d{9}$");
const QRegularExpression AddNewEmployees::regexNull = QRegularExpression("^\\s*$");

AddNewEmployees::AddNewEmployees(AddEmployeesViewModel* addEmployeesViewModel, QWidget *parent) :
    addEmployeesViewModel(addEmployeesViewModel),
    QDialog(parent),
    ui(new Ui::AddNewEmployees)
{
    ui->setupUi(this);
    notification = new CenteredNotification;
    connected();

    addEmployeesViewModel->update();
    ui->inputPhoneNumber->setValidator(new QRegularExpressionValidator(regexNumberPhone));
}

void AddNewEmployees::addItemsToComboBox(const QStringList& first, const QStringList& second)
{
    ui->comboBoxGender->addItems(first);
    ui->comboBoxPosition->addItems(second);
    ui->comboBoxGender->setCurrentIndex(-1);
    ui->comboBoxPosition->setCurrentIndex(-1);
}

void AddNewEmployees::show()
{
    addEmployeesViewModel->update();
    QWidget::show();
}

void AddNewEmployees::hide()
{
    QWidget::hide();
}

void AddNewEmployees::close()
{
    FormWithButtonBack::clearStack();
}

void AddNewEmployees::connected()
{
    connect(addEmployeesViewModel, &AddEmployeesViewModel::addItemsToComboBox, this, &AddNewEmployees::addItemsToComboBox);
    connect(addEmployeesViewModel, &AddEmployeesViewModel::close, this, &AddNewEmployees::close);

    //Добавление
    connect(ui->buttonAddEmployees, &QPushButton::clicked, this, [&]()
    {
        QList<QLineEdit*> list = {ui->inputFullName, ui->inputPassword, ui->inputAddress, ui->inputPhoneNumber};

        for (QLineEdit* item : list)
            if(regexNull.match(item->text()).hasMatch())
                return notification->show("Заповніть усі ключові поля!", 2);

        if(ui->comboBoxGender->currentIndex() == -1 ||ui->comboBoxPosition->currentIndex() == -1)
            return notification->show("Заповніть усі ключові поля!", 2);

        if(!regexNumberPhone.match(ui->inputPhoneNumber->text()).hasMatch())
            return notification->show("Введіть коректний номер телефону!", 2);

        addEmployeesViewModel->applyChanges(ui->inputFullName->text(), ui->inputPassword->text(), ui->comboBoxPosition->currentText(), ui->inputPhoneNumber->text(), ui->inputAddress->text(), ui->comboBoxGender->currentText(), ui->dateEdit->date().toString("yyyy.MM.dd"));
    });
}

AddNewEmployees::~AddNewEmployees()
{
    delete notification;
    delete addEmployeesViewModel;
    delete ui;
}
