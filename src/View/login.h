#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMessageBox>

#include "loginviewmodel.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(std::shared_ptr<LoginViewModel> loginViewModel, QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_Button_Login_clicked();
    void openMainWindow();
    void openFailedDialog();
    void on_Button_Exit_clicked();

private:
    Ui::Login *ui;
    std::shared_ptr<LoginViewModel> loginViewModel;
};

#endif // LOGIN_H
