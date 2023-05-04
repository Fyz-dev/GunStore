#ifndef ELEMENTORDER_H
#define ELEMENTORDER_H

#include <QWidget>

namespace Ui {
class ElementOrder;
}

class ElementOrder : public QWidget
{
    Q_OBJECT

public:
    explicit ElementOrder(QWidget *parent = nullptr);
    ~ElementOrder();

private:
    Ui::ElementOrder *ui;
};

#endif // ELEMENTORDER_H
