#ifndef MENUSUPPLIER_H
#define MENUSUPPLIER_H

#include "suppliermodel.h"
#include "iview.h"

#include <QWidget>

namespace Ui {
class MenuSupplier;
}

class MenuSupplier : public QWidget, public IView
{
    Q_OBJECT

public:
    explicit MenuSupplier(SupplierModel* supplierModel, QWidget *parent = nullptr);
    ~MenuSupplier();

    void show() override;
    void hide() override;

signals:
    void openAddSupplier();

private:
    void update();

private:
    Ui::MenuSupplier *ui;
    SupplierModel* supplierModel;
};

#endif // MENUSUPPLIER_H
