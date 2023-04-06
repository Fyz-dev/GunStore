#ifndef MENUSUPPLIER_H
#define MENUSUPPLIER_H

#include <QWidget>

namespace Ui {
class MenuSupplier;
}

class MenuSupplier : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSupplier(QWidget *parent = nullptr);
    ~MenuSupplier();

private:
    Ui::MenuSupplier *ui;
};

#endif // MENUSUPPLIER_H
