#ifndef FORMWITHTABLE_H
#define FORMWITHTABLE_H

#include <QWidget>
#include <buyermodel.h>

namespace Ui {
class FormWithTable;
}

class FormWithTable : public QWidget
{
    Q_OBJECT

public:
    explicit FormWithTable(const QString& identifier, const QString& title, const QString& sum, BuyerModel* buyerModel, QWidget *parent = nullptr);
    ~FormWithTable();

private:
    Ui::FormWithTable *ui;
};

#endif // FORMWITHTABLE_H
