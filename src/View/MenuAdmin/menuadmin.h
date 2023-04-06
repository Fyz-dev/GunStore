#ifndef MENUADMIN_H
#define MENUADMIN_H

#include <QWidget>

namespace Ui {
class MenuAdmin;
}

class MenuAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit MenuAdmin(QWidget *parent = nullptr);
    ~MenuAdmin();

private:
    Ui::MenuAdmin *ui;
};

#endif // MENUADMIN_H
