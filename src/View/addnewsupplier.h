#ifndef ADDNEWSUPPLIER_H
#define ADDNEWSUPPLIER_H

#include "suppliermodel.h"

#include <QDialog>

namespace Ui {
class AddNewSupplier;
}

class AddNewSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewSupplier(SupplierModel* supplierModel, QWidget *parent = nullptr);
    ~AddNewSupplier();

private:
    Ui::AddNewSupplier *ui;
    SupplierModel* supplierModel;
};

#endif // ADDNEWSUPPLIER_H
