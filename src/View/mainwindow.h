#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "WindowState.h"
#include "LayoutState.h"
#include "mainwindowmediator.h"

#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainWindowMediator* mainWindowMediator, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void buttonMainMenu_clicked();

    void on_buttonAdmin_clicked();

    void on_buttonAddNewProduct_clicked();

    void on_buttonInfoEmployees_clicked();

    void on_buttonReportCheck_clicked();

    void on_buttonEditBD_clicked();

    void on_buttonAddEmployees_clicked();

    void on_buttonBuyProduct_clicked();

    void on_buttonInfoBuyer_clicked();

    void on_buttonInfoSupplier_clicked();

    void on_buttonAddSupplier_clicked();

    void on_buttonBasket_clicked();

public slots:
    void modelChangedSlots(QSqlTableModel* modelData);
    void addCheckBoxSlots(QCheckBox* checkBox, LayoutState& layoutName);
    void clearCheckBoxSlots();

private:
    void connected();

private:
    Ui::MainWindow *ui;
    WindowState windowState;
    MainWindowMediator* mainWindowMediator;
};
#endif // MAINWINDOW_H
