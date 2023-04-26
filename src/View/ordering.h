#ifndef ORDERING_H
#define ORDERING_H

#include <QDialog>

namespace Ui {
class Ordering;
}

class Ordering : public QDialog
{
    Q_OBJECT

public:
    explicit Ordering(QWidget *parent = nullptr);
    ~Ordering();

signals:
    void closeMe();

private:
    void connected();

private:
    Ui::Ordering *ui;
};

#endif // ORDERING_H
