#include "login.h"
#include "connectionhandler.h"
#include "mainwindow.h"
#include "productmodel.h"
#include "mainmenuviewmodel.h"
#include "mainwindowmediator.h"

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
        std::unique_ptr<ProductModel> productModel = std::make_unique<ProductModel>(connectionHandler->getDB());
        std::unique_ptr<MainMenuViewModel> mainMenuViewModel = std::make_unique<MainMenuViewModel>(productModel.get());
        std::unique_ptr<MainWindowMediator> mainWindowMediator = std::make_unique<MainWindowMediator>(mainMenuViewModel.get());
        std::unique_ptr<MainWindow> formMainWindow = std::make_unique<MainWindow>(mainWindowMediator.get());
        formMainWindow->show();
        a.exec();
    }

    return 0;
}
