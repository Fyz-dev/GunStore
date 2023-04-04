#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include <QObject>
#include "connectionhandler.h"

class LoginViewModel : public QObject
{
    Q_OBJECT

public:
    LoginViewModel(std::shared_ptr<ConnectionHandler> connectionHandler);

public:
    void connectedBD(QString userName, QString password);

signals:
    void openMainWindowSignal();
    void openFailedDialogSignal();

private:
    std::shared_ptr<ConnectionHandler> connectionHandler;
};

#endif // LOGINVIEWMODEL_H
