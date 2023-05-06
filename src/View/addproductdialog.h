#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include "addproductdialogviewmodel.h"
#include "centerednotification.h"

#include <QDialog>
#include <QComboBox>
#include <QTableWidget>

namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(AddProductDialogViewModel* addProductDialogViewModel, QWidget *parent = nullptr);
    ~AddProductDialog();

public slots:
    void updateComboBoxSlots(const QString& text);
    void setComboBoxSlots(QComboBox* comboBox);

signals:
    void selectedItemComboBox(const int& i, const QComboBox* comboBoxSender);
    void addNewProduct(const QString& name, const QString& price, const QString& brand, const QString& weight, const QString& package, const QString& country, const QString& category, const QTableWidget* table);

private slots:
    void connected();
    void valueEnteredTableWidget(const int& row, const int& column);

private:
    //bool isValidInput(QLineEdit* lineEdit);

private:
    Ui::AddProductDialog *ui;
    static const QRegularExpression regex;
    static const QRegularExpression regexNull;
    AddProductDialogViewModel* addProductDialogViewModel;
    CenteredNotification* notification;

    int previousIndexComboBox;
};

#endif // ADDPRODUCTDIALOG_H
