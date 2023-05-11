#ifndef MENUSUPPLIER_H
#define MENUSUPPLIER_H

#include "suppliermodel.h"
#include "iview.h"
#include "isearch.h"

#include <QWidget>

namespace Ui {
class MenuSupplier;
}

class MenuSupplier : public QWidget, public IView, public ISearch
{
    Q_OBJECT

public:
    explicit MenuSupplier(SupplierModel* supplierModel, QWidget *parent = nullptr);
    ~MenuSupplier();

    void search(const QString& text) override;

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
