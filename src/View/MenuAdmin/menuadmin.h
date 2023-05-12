#ifndef MENUADMIN_H
#define MENUADMIN_H

#include "basemodel.h"
#include "baseviewmodel.h"
#include "connectionhandler.h"
#include "iview.h"

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QPropertyAnimation>

namespace Ui {
class MenuAdmin;
}

class MenuAdmin : public QWidget, public IView
{
    Q_OBJECT

public:
    explicit MenuAdmin(ConnectionHandler* connectionHandler, QLineEdit* lineSearch, QWidget *parent = nullptr);
    ~MenuAdmin();

public slots:
    void openAddNewProductDialog();
    void openAddNewEmployees();
    void openAddSupplier();
    QWidget* getThisWindow() { return thisWindow; }

    void show() override;
    void hide() override;

private slots:
    void buttonEditProduct_clicked();
    void buttonInfoEmployees_clicked();
    void buttonInfoSupplier_clicked();
    void buttonInfoBuyer_clicked();
    void buttonReportCheck_clicked();

private:
    void colorButtonControl(QPushButton* sender);
    void freeMemory();
    void connected();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MenuAdmin *ui;
    QWidget* thisWindow = nullptr;
    BaseModel* thisModel = nullptr;
    BaseViewModel* thisViewModel = nullptr;
    QPushButton* thisButton = nullptr;
    ConnectionHandler* connectionHandler;
    QLineEdit* lineSearch;
    QPropertyAnimation* animation;
};

#endif // MENUADMIN_H
