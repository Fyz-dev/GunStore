#ifndef FORMPEOPLE_H
#define FORMPEOPLE_H

#include "basemodel.h"
#include "elementorder.h"
#include "iview.h"

#include <QWidget>

namespace Ui {
class FormPeople;
}

class FormPeople : public QWidget, public IView
{
    Q_OBJECT

public:
    explicit FormPeople(const QString& INN, const QString& FIO, BaseModel* model, QWidget *parent = nullptr);
    FormPeople(const QString& identifier, SupplierModel* model, QWidget *parent = nullptr);
    ~FormPeople();

    void show() override;
    void hide() override;

private slots:
    void buttonDetails_clicked();

private:
    FormPeople(const QString& identifier, BaseModel* model, QWidget *parent = nullptr);
    void addToView();
    void updateSupplier();

private:
    Ui::FormPeople *ui;
    BaseModel* model;
    QString identifier;
    QList<ElementOrder*> list;
};

#endif // FORMPEOPLE_H
