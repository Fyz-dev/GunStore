#ifndef ADDCHARACT_H
#define ADDCHARACT_H

#include "productmodel.h"
#include "centerednotification.h"

#include <QWidget>

namespace Ui {
class AddCharact;
}

class AddCharact : public QWidget
{
    Q_OBJECT

public:
    explicit AddCharact(ProductModel* productModel, QWidget *parent = nullptr);
    ~AddCharact();

private slots:
    void comboBoxCategoryIndexChanged(const int& i);
    void comboBoxCharactIndexChanged(const int& i);
    void valueEnteredTableWidget(const int& row, const int& column);
    void buttonApply_clicked();

private:
    Ui::AddCharact *ui;
    ProductModel* productModel;
    CenteredNotification* notification;
    QList<QString> listCharact;
};

#endif // ADDCHARACT_H
