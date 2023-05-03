#ifndef ELEMENTPEOPLE_H
#define ELEMENTPEOPLE_H

#include <QWidget>

namespace Ui {
class ElementPeople;
}

class ElementPeople : public QWidget
{
    Q_OBJECT

public:
    explicit ElementPeople(QWidget *parent = nullptr);
    ~ElementPeople();

private:
    Ui::ElementPeople *ui;
};

#endif // ELEMENTPEOPLE_H
