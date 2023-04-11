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
    explicit BaseViewModelForProduct(ProductModel* productModel, QString standartRequest = "select p_name as 'Назва', p_priceOne as 'Ціна(грн.)', p_count as 'Кількість(шт.)', p_brand as 'Бренд', p_weight as 'Вес(г.)',p_package as 'Упаковка', p_country as 'Країна', c_name as 'Категорія' from product join category using(id_category)");
    ~BaseViewModelForProduct();

public slots:
    void checkBoxEnabledSlots(const int& state);
    void priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo);
    void selectedElemTableViewSlots(const QModelIndex& i);

signals:
    void modelChangedSignal(QSqlTableModel* modelData);
    void addCheckBoxSignal(QCheckBox* checkBox, const LayoutState& layoutName);
    void addInfoProductSignal(QLabel* label = nullptr, QLineEdit* lineEdit = nullptr);
    void clearCheckBoxSignal();
    void clearLableSignal();

protected:
    ProductModel* productModel;
    Filter* filter;
};

#endif // BASEVIEWMODELFORPRODUCT_H
