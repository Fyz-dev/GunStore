#ifndef FORMFOREMPTY_H
#define FORMFOREMPTY_H

#include <QWidget>

namespace Ui {
class FormForEmpty;
}

class FormForEmpty : public QWidget
{
    Q_OBJECT

public:
    explicit FormForEmpty(QWidget *parent = nullptr);
    ~FormForEmpty();

private:
    Ui::FormForEmpty *ui;
};

#endif // FORMFOREMPTY_H
