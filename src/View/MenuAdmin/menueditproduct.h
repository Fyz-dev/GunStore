#ifndef MENUEDITPRODUCT_H
#define MENUEDITPRODUCT_H

#include "menueditproductviewmodel.h"
#include "iview.h"
#include "isearch.h"

#include <QMessageBox>
#include <QWidget>


namespace Ui {
class MenuEditProduct;
}

class MenuEditProduct : public QWidget, public IView, public ISearch
{
    Q_OBJECT

public:
    explicit MenuEditProduct(MenuEditProductViewModel* menuEditProductViewModel, QWidget *parent = nullptr);
    ~MenuEditProduct();

    void search(const QString& text) override;

public slots:
    void modelChangedSlots(QAbstractTableModel* modelData);
    void addCheckBoxSlots(QCheckBox* checkBox, const LayoutState& layoutName);
    void addInfoProductSlots(QWidget* widget = nullptr);
    void clearCheckBoxSlots();
    void clearLableSlots();
    void priceFilterChangedSlots();
    void showMessageBox();

    void show() override;
    void hide() override;

signals:
    void priceFilterChangedSignals(QLineEdit* inputTo, QLineEdit* inputDo, const QString& isDelete);
    void openAddNewProductDialogSignals();

private:
    void connected();
    void deleteWidget(QLayout* layout);

private:
    Ui::MenuEditProduct *ui;
    MenuEditProductViewModel* menuEditProductViewModel;
};

#endif // MENUEDITPRODUCT_H
