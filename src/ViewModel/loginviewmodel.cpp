#include "loginviewmodel.h"

LoginViewModel::LoginViewModel(std::shared_ptr<ConnectionHandler> connectionHandler) :
    connectionHandler(connectionHandler)
{}

void LoginViewModel::connectedBD(QString userName, QString password)
{
    if(connectionHandler->connectionDataBase(userName, password))
    {
        emit openMainWindowSignal();
        return;
    }

    emit openFailedDialogSignal();
}
