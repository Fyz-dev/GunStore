#ifndef MAINMENUVIEWMODEL_H
#define MAINMENUVIEWMODEL_H

#include "productmodel.h"
#include "LayoutState.h"

#include <QSqlTableModel>
#include <QCheckBox>

class MainMenuViewModel : public QObject
{
Q_OBJECT

public:
    MainMenuViewModel(ProductModel* productModel);
    void update();

public slots:
    void checkBoxEnabledSlots(int state);

signals:
    void modelChangedSignal(QSqlTableModel* modelData);
    void addCheckBoxSignal(QCheckBox* checkBox, LayoutState& layoutName);
    void clearCheckBoxSignal();

private:
    void createCheckBox(QList<QString> list, LayoutState layoutName);
    void updateModelByFilter();

private:
    ProductModel* productModel;
    QList<QObject*> listCheckBoxEnabled;
    QString standartRequest;
};

#endif // MAINMENUVIEWMODEL_H
