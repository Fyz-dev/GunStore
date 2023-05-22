#ifndef ADDBUYER_H
#define ADDBUYER_H

#include "productmodel.h"
#include "centerednotification.h"

#include <QWidget>

namespace Ui {
class AddBuyer;
}

class AddBuyer : public QWidget
{
    Q_OBJECT

public:
    explicit AddBuyer(ProductModel* productModel, QHash<int, int>& listProduct, QWidget *parent = nullptr);
    AddBuyer(const QString& FIO, const QString& INN, const QString& numberPhone, const QString& email, const QString& city, const QString& details, const QString& license, QWidget *parent = nullptr);
    ~AddBuyer();

private slots:
    void buttonOrder_clicked();
    void comboBoxIndexChanged(const int& i);
    void inputNewFIO();

private:
    AddBuyer(QWidget *parent = nullptr);
    void connected();
    void setEditable(bool isEdit);

private:
    Ui::AddBuyer *ui;
    ProductModel* productModel;
    QHash<int, int>* listProduct;
    CenteredNotification* notification;

    static QRegularExpression regexFIO;
    static QRegularExpression regexNumberPhone;
    static QRegularExpression regexEmail;
    static QRegularExpression regexINN;
    static QRegularExpression regexLicense;
};

#endif // ADDBUYER_H
