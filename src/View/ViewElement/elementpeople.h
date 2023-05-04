#ifndef ELEMENTPEOPLE_H
#define ELEMENTPEOPLE_H

#include "connectionhandler.h"
#include "basemodel.h"

#include <QWidget>

namespace Ui {
class ElementPeople;
}

class ElementPeople : public QWidget
{
    Q_OBJECT

public:
    explicit ElementPeople(const QString& INN, const QString& FIO, const QString& numberPhone, const QString& address, ConnectionHandler* connection, QWidget *parent = nullptr);
    ~ElementPeople();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::ElementPeople *ui;

    QString INN;
    QString FIO;
    ConnectionHandler* connectionHandler;
    BaseModel* model = nullptr;
};

#endif // ELEMENTPEOPLE_H
