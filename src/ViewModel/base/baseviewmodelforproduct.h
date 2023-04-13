#ifndef BASEVIEWMODELFORPRODUCT_H
#define BASEVIEWMODELFORPRODUCT_H

#include <QObject>
#include "baseviewmodel.h"
#include "productmodel.h"
#include "LayoutState.h"
#include "filter.h"


class BaseViewModelForProduct : public QObject, public BaseViewModel
{
    Q_OBJECT
public:
    explicit BaseViewModelForProduct(ProductModel* productModel, QString standartRequest = "");
    ~BaseViewModelForProduct();
    void selectedElemTableViewSlots(const QModelIndex& i, bool lineEditIsReadOnly = true);

public slots:
    void checkBoxEnabledSlots(const int& state);
    void priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo);

signals:
    void modelChangedSignal(QSqlTableModel* modelData);
    void addCheckBoxSignal(QCheckBox* checkBox, const LayoutState& layoutName);
    void addInfoProductSignal(QWidget* widget = nullptr);
    void clearCheckBoxSignal();
    void clearLableSignal();

protected:
    virtual void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName) = 0;

protected:
    ProductModel* productModel;
    Filter* filter;
};

#endif // BASEVIEWMODELFORPRODUCT_H
