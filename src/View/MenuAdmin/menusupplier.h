#ifndef MENUSUPPLIER_H
#define MENUSUPPLIER_H

#include "menusupplierviewmodel.h"

#include <QWidget>

namespace Ui {
class MenuSupplier;
}

class MenuSupplier : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSupplier(MenuSupplierViewModel* menuSupplierViewModel, QWidget *parent = nullptr);
    ~MenuSupplier();

public slots:
    void modelChangedSlots(QAbstractItemModel* model);

signals:
    void openAddSupplier();

private:
    void connected();

private:
    Ui::MenuSupplier *ui;
    MenuSupplierViewModel* menuSupplierViewModel;
};

#endif // MENUSUPPLIER_H
