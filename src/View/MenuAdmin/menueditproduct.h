#ifndef MENUEDITPRODUCT_H
#define MENUEDITPRODUCT_H

#include "menueditproductviewmodel.h"

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
    void addInfoProductSlots(QLabel* label = nullptr, QLineEdit* lineEdit = nullptr);
    void clearCheckBoxSlots();
    void clearLableSlots();
    void priceFilterChangedSlots();

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
