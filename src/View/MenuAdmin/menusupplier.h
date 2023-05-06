#ifndef MENUSUPPLIER_H
#define MENUSUPPLIER_H

#include "suppliermodel.h"

#include <QWidget>

namespace Ui {
class MenuSupplier;
}

class MenuSupplier : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSupplier(SupplierModel* supplierModel, QWidget *parent = nullptr);
    ~MenuSupplier();

signals:
    void openAddSupplier();

private:
    void update();

private:
    Ui::MenuSupplier *ui;
    SupplierModel* supplierModel;
};

#endif // MENUSUPPLIER_H
