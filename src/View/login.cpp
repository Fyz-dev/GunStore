#include "login.h"
#include "ui_login.h"

Login::Login(std::shared_ptr<LoginViewModel> loginViewModel, QWidget *parent) :
    loginViewModel(loginViewModel),
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(loginViewModel.get(), &LoginViewModel::openMainWindowSignal, this, &Login::openMainWindow);
    connect(loginViewModel.get(), &LoginViewModel::openFailedDialogSignal, this, &Login::openFailedDialog);

}

void Login::on_Button_Login_clicked()
{
    //loginViewModel->connectedBD(ui->lineEdit_Login->text(), ui->lineEdit_Password->text());
    loginViewModel->connectedBD("admin", "admin");
}

void Login::on_Button_Exit_clicked()
{
    this->close();
}

void Login::openMainWindow()
{
    this->close();
    QApplication::exit(13);
}

void Login::openFailedDialog()
{
    QMessageBox::warning(this, tr("Помилка!"), tr("Ви ввели некоректні дані!"));
}

Login::~Login()
{
    delete ui;
}

