#ifndef MENUEDITPRODUCT_H
#define MENUEDITPRODUCT_H

#include "menueditproductviewmodel.h"
#include "connectionhandler.h"
#include "iview.h"
#include "isearch.h"
#include "iclose.h"
#include "centerednotification.h"

#include <QMessageBox>
#include <QWidget>


namespace Ui {
class MenuEditProduct;
}

class MenuEditProduct : public QWidget, public IView, public ISearch, public IClose
{
    Q_OBJECT

public:
    explicit MenuEditProduct(MenuEditProductViewModel* menuEditProductViewModel, ConnectionHandler* connectionHandler, QWidget *parent = nullptr);
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

    bool canClose() override;
    void show() override;
    void hide() override;

signals:
    void priceFilterChangedSignals(QLineEdit* inputTo, QLineEdit* inputDo, const QString& isDelete);
    void openAddNewProductDialogSignals();

private slots:
    void selectedItem(const QModelIndex& i);

private:
    void connected();
    void deleteWidget(QLayout* layout);
    void buttonAddCharact(QComboBox* comboBox, QLineEdit* lineEdit);

private:
    Ui::MenuEditProduct *ui;
    MenuEditProductViewModel* menuEditProductViewModel;
    ConnectionHandler* connectionHandler;
    CenteredNotification* notification;

    static const QRegularExpression regexNull;
};

#endif // MENUEDITPRODUCT_H
