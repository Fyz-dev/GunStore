#ifndef MAINMENUVIEWMODEL_H
#define MAINMENUVIEWMODEL_H

#include "productmodel.h"
#include "LayoutState.h"
#include "baseviewmodel.h"

#include <QSqlTableModel>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>

class MainMenuViewModel : public QObject, public BaseViewModel
{
Q_OBJECT

public:
    MainMenuViewModel(ProductModel* productModel);
    void update() override;

public slots:
    void checkBoxEnabledSlots(const int& state);
    void priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo);
    void selectedElemTableViewSlots(const QModelIndex& i);

signals:
    void modelChangedSignal(QSqlTableModel* modelData);
    void addCheckBoxSignal(QCheckBox* checkBox, LayoutState& layoutName);
    void addInfoProductSignal(QLabel* label = nullptr, QLineEdit* lineEdit = nullptr);
    void clearCheckBoxSignal();
    void clearLableSignal();

private:
    void createCheckBox(const QList<QString>& list, LayoutState layoutName);
    void createLable(const QHash<QString, QString>& list);
    void updateModelByFilter();

private:
    ProductModel* productModel;
    QList<QObject*> listCheckBoxEnabled;
    QList<QObject*> listLabelCharacteristic;
    QString priceTo, priceDo;
};

#endif // MAINMENUVIEWMODEL_H
