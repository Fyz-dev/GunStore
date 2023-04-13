#ifndef BASEVIEWMODEL_H
#define BASEVIEWMODEL_H

#include <QString>

class BaseViewModel
{
public:
    BaseViewModel(QString standartRequest = "");
    virtual ~BaseViewModel();
    virtual void update() = 0;

protected:
    QString standartRequest;
};

#endif // BASEVIEWMODEL_H
