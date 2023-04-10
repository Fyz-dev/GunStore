#ifndef MAINMENUVIEWMODEL_H
#define MAINMENUVIEWMODEL_H

#include "productmodel.h"
#include "LayoutState.h"
#include "baseviewmodel.h"
#include "filter.h"



class MainMenuViewModel : public QObject, public BaseViewModel
{
Q_OBJECT

public:
    MainMenuViewModel(ProductModel* productModel);
    ~MainMenuViewModel();
    void update() override;

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

private:
    void addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName);

private:
    ProductModel* productModel;
    Filter* filter;
};

#endif // MAINMENUVIEWMODEL_H
