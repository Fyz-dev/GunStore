#ifndef MENUEMPLOYEES_H
#define MENUEMPLOYEES_H

#include <QWidget>

namespace Ui {
class MenuEmployees;
}

class MenuEmployees : public QWidget
{
    Q_OBJECT

public:
    explicit MenuEmployees(QWidget *parent = nullptr);
    ~MenuEmployees();

private:
    Ui::MenuEmployees *ui;
};

#endif // MENUEMPLOYEES_H
