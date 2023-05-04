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
    explicit FormWithTable(const QString& INN, BuyerModel* buyerModel, QWidget *parent = nullptr);
    ~FormWithTable();

private:
    Ui::FormWithTable *ui;
};

#endif // FORMWITHTABLE_H
