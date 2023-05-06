#ifndef ELEMENTPEOPLE_H
#define ELEMENTPEOPLE_H

#include "connectionhandler.h"
#include "basemodel.h"

#include <QWidget>

enum class People
{
    Buyer,
    Supplier,
    Employees
};

namespace Ui {
class ElementPeople;
}

class ElementPeople : public QWidget
{
    Q_OBJECT

public:
    explicit ElementPeople(const QString& INN, const QString& FIO, const QString& numberPhone, const QString& address, ConnectionHandler* connectionHandler, QWidget *parent = nullptr);
    ElementPeople(const QString& idSupplier, const QString& SupplierName, const QString& edrpou, const QString& numberPhone, const QString& address, ConnectionHandler* connectionHandler, QWidget *parent = nullptr);
    ElementPeople(const QString& idWorker, const QString& FIO, const QString& position, const QString& numberPhone, const QString& address, QWidget *parent, ConnectionHandler* connectionHandler);
    ~ElementPeople();

private:
    ElementPeople(const QString& identifier, const QString& numberPhone, const QString& address, ConnectionHandler* connectionHandler, QWidget* parent);

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::ElementPeople *ui;

    QString identifier;
    QString title;
    QString titleBottom;

    ConnectionHandler* connectionHandler;
    BaseModel* model = nullptr;
    People people;
};

#endif // ELEMENTPEOPLE_H
