#ifndef MENUEDITPRODUCT_H
#define MENUEDITPRODUCT_H

#include "menueditproductviewmodel.h"
#include <QMessageBox>

#include <QWidget>


namespace Ui {
class MenuEditProduct;
}

class MenuEditProduct : public QWidget
{
    Q_OBJECT

public:
    explicit MenuEditProduct(MenuEditProductViewModel* menuEditProductViewModel, QWidget *parent = nullptr);
    ~MenuEditProduct();

public slots:
    void modelChangedSlots(QAbstractTableModel* modelData);
    void addCheckBoxSlots(QCheckBox* checkBox, const LayoutState& layoutName);
    void addInfoProductSlots(QWidget* widget = nullptr);
    void clearCheckBoxSlots();
    void clearLableSlots();
    void priceFilterChangedSlots();
    void showMessageBox();

signals:
    void priceFilterChangedSignals(QLineEdit* inputTo, QLineEdit* inputDo);

private:
    void connected();
    void deleteWidget(QLayout* layout);

private:
    Ui::MenuEditProduct *ui;
    MenuEditProductViewModel* menuEditProductViewModel;
};

#endif // MENUEDITPRODUCT_H
