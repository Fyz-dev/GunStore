#ifndef FORMWITHTABLE_H
#define FORMWITHTABLE_H

#include <QWidget>
#include "buyermodel.h"
#include "suppliermodel.h"

namespace Ui {
class FormWithTable;
}

class FormWithTable : public QWidget
{
    Q_OBJECT

public:
    explicit FormWithTable(const QString& identifier, const QString& title, const QString& sum, BuyerModel* buyerModel, QWidget *parent = nullptr);
    explicit FormWithTable(const QString& identifier, const QString& title, const QString& sum, SupplierModel* supplierModel, QWidget *parent = nullptr);
    ~FormWithTable();

private:
    FormWithTable(const QString& identifier, const QString& sum, QWidget *parent = nullptr);

private:
    Ui::FormWithTable *ui;
};

#endif // FORMWITHTABLE_H
