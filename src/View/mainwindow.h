#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basemodel.h"
#include "baseviewmodel.h"
#include "connectionhandler.h"
#include "formwithbuttonback.h"

#include <QMainWindow>
#include <QSqlTableModel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ConnectionHandler* connectionHandler, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void buttonMainMenu_clicked();
    void buttonBuyProduct_clicked();
    void buttonAdmin_clicked();
    void buttonBasket_clicked();
    void search(const QString& text);

private:
    void connected();
    void freeMemory();
    void colorButtonControl(QPushButton* sender);

private:
    Ui::MainWindow *ui;

    QPushButton* thisButton = nullptr;
    QWidget* thisWindow = nullptr;
    BaseModel* thisModel = nullptr;
    BaseViewModel* thisViewModel;

    FormWithButtonBack* formWithButtonBack;
    ConnectionHandler* connectionHandler;
};
#endif // MAINWINDOW_H
