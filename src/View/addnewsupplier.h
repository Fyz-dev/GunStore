#ifndef ADDNEWSUPPLIER_H
#define ADDNEWSUPPLIER_H

#include "suppliermodel.h"
#include "centerednotification.h"

#include <QDialog>
#include <QRegularExpression>

namespace Ui {
class AddNewSupplier;
}

class AddNewSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewSupplier(SupplierModel* supplierModel, QWidget *parent = nullptr);
    AddNewSupplier(const QString& idSupplier, SupplierModel* supplierModel, QWidget* parent = nullptr);
    ~AddNewSupplier();

private:
    AddNewSupplier(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Ui::AddNewSupplier *ui;
    SupplierModel* supplierModel;
    CenteredNotification* notification;
    QString lastText;
    static const QRegularExpression regexNumberPhone;
    static const QRegularExpression regexNull;
    static const QRegularExpression regexEdrpou;
    static const QRegularExpression regexBank;
};

#endif // ADDNEWSUPPLIER_H
