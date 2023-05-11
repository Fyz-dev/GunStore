#ifndef MENUBUYER_H
#define MENUBUYER_H

#include "buyermodel.h"
#include "isearch.h"

#include <QWidget>

namespace Ui {
class MenuBuyer;
}

class MenuBuyer : public QWidget, public ISearch
{
    Q_OBJECT

public:
    explicit MenuBuyer(BuyerModel* buyerModel, QWidget *parent = nullptr);
    ~MenuBuyer();

    void search(const QString& text) override;

private:
    void update();

private:
    Ui::MenuBuyer *ui;
    BuyerModel* buyerModel;
};

#endif // MENUBUYER_H
