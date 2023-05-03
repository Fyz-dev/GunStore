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
    explicit ElementPeople(const QString& INN, const QString& FIO, const QString& numberPhone, const QString& address, QWidget *parent = nullptr);
    ~ElementPeople();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    Ui::ElementPeople *ui;

    QString INN;
};

#endif // ELEMENTPEOPLE_H
