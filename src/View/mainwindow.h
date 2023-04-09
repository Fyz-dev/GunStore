#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basemodel.h"
#include "baseviewmodel.h"
#include "connectionhandler.h"

#include <QMainWindow>
#include <QSqlTableModel>

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

private:
    void connected();
    void freeMemory();

private:
    Ui::MainWindow *ui;
    QWidget* thisWindow;
    BaseModel* thisModel;
    BaseViewModel* thisViewModel;
    ConnectionHandler* connectionHandler;
};
#endif // MAINWINDOW_H
