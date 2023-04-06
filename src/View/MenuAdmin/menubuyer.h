#ifndef MENUBUYER_H
#define MENUBUYER_H

#include <QWidget>

namespace Ui {
class MenuBuyer;
}

class MenuBuyer : public QWidget
{
    Q_OBJECT

public:
    explicit MenuBuyer(QWidget *parent = nullptr);
    ~MenuBuyer();

private:
    Ui::MenuBuyer *ui;
};

#endif // MENUBUYER_H
