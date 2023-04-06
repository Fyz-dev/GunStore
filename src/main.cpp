#include "login.h"
#include "connectionhandler.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<ConnectionHandler> connectionHandler = std::make_shared<ConnectionHandler>();
    std::shared_ptr<LoginViewModel> loginViewModel = std::make_shared<LoginViewModel>(connectionHandler);
    Login login(loginViewModel);

    login.show();

    if(a.exec() == 13)
    {
        std::unique_ptr<MainWindow> formMainWindow = std::make_unique<MainWindow>(connectionHandler.get());
        formMainWindow->show();
        a.exec();
    }

    return 0;
}
