#ifndef MENUADMIN_H
#define MENUADMIN_H

#include "basemodel.h"
#include "baseviewmodel.h"
#include "connectionhandler.h"

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MenuAdmin;
}

class MenuAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit MenuAdmin(ConnectionHandler* connectionHandler, QWidget *parent = nullptr);
    ~MenuAdmin();

public slots:
    void openAddNewProductDialog();
    void openAddNewEmployees();
    void openAddSupplier();

private slots:
    void buttonEditProduct_clicked();
    void buttonInfoEmployees_clicked();
    void buttonInfoSupplier_clicked();
    void buttonInfoBuyer_clicked();

private:
    void colorButtonControl(QPushButton* sender);
    void freeMemory();
    void connected();

private:
    Ui::MenuAdmin *ui;
    QWidget* thisWindow = nullptr;
    BaseModel* thisModel = nullptr;
    BaseViewModel* thisViewModel = nullptr;
    QPushButton* thisButton = nullptr;
    ConnectionHandler* connectionHandler;
};

#endif // MENUADMIN_H
