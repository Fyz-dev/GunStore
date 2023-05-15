#ifndef ADDPRODUCTDIALOGVIEWMODEL_H
#define ADDPRODUCTDIALOGVIEWMODEL_H

#include "baseviewmodel.h"
#include "productmodel.h"

#include <QComboBox>
#include <QTableWidget>

class AddProductDialogViewModel : public QObject, public BaseViewModel
{
    Q_OBJECT

public:
    AddProductDialogViewModel(ProductModel* productModel);
    ~AddProductDialogViewModel();
    void update() override;
    void addNewProduct(const QString& name, const QString& price, const QString& brand, const QString& weight, const QString& package, const QString& country, const QString& category, const QTableWidget* table);

public slots:
    void selectedItemComboBox(const int& i, const QComboBox* comboBoxSender);

signals:
    void updateComboBoxSignals(const QString& text);
    void setComboBoxSignals(QComboBox* comboBox);

private:
    void createCheckBox(const QList<QString>& list);

private:
    ProductModel* productModel;
};

#endif // ADDPRODUCTDIALOGVIEWMODEL_H
