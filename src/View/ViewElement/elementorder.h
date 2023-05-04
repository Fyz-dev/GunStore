#ifndef ELEMENTORDER_H
#define ELEMENTORDER_H

#include "buyermodel.h"

#include <QWidget>

namespace Ui {
class ElementOrder;
}

class ElementOrder : public QWidget
{
    Q_OBJECT

public:
    explicit ElementOrder(const QString& identifier, const QString& Title, const QString& count, const QString sum, BuyerModel* model, QWidget *parent = nullptr);
    ~ElementOrder();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::ElementOrder *ui;
    QString identifier;
    QString count;
    QString sum;
    BuyerModel* model;
};

#endif // ELEMENTORDER_H
