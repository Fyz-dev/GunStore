#ifndef MENUADMIN_H
#define MENUADMIN_H

#include "basemodel.h"
#include "baseviewmodel.h"
#include "connectionhandler.h"

#include <QWidget>

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

private slots:
    void buttonEditProduct_clicked();

private:
    void freeMemory();
    void connected();

private:
    Ui::MenuAdmin *ui;
    QWidget* thisWindow;
    BaseModel* thisModel;
    BaseViewModel* thisViewModel;
    ConnectionHandler* connectionHandler;
};

#endif // MENUADMIN_H
