#ifndef FORMPEOPLE_H
#define FORMPEOPLE_H

#include "basemodel.h"

#include <QWidget>

namespace Ui {
class FormPeople;
}

class FormPeople : public QWidget
{
    Q_OBJECT

public:
    explicit FormPeople(const QString& INN, const QString& FIO, BaseModel* model, QWidget *parent = nullptr);
    ~FormPeople();

    void update();

private:
    Ui::FormPeople *ui;
    BaseModel* model;
};

#endif // FORMPEOPLE_H
