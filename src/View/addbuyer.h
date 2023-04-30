#ifndef ADDBUYER_H
#define ADDBUYER_H

#include <QWidget>

namespace Ui {
class AddBuyer;
}

class AddBuyer : public QWidget
{
    Q_OBJECT

public:
    explicit AddBuyer(QWidget *parent = nullptr);
    ~AddBuyer();

private:
    Ui::AddBuyer *ui;
};

#endif // ADDBUYER_H
