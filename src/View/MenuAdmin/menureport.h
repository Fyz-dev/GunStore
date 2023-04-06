#ifndef MENUREPORT_H
#define MENUREPORT_H

#include <QWidget>

namespace Ui {
class MenuReport;
}

class MenuReport : public QWidget
{
    Q_OBJECT

public:
    explicit MenuReport(QWidget *parent = nullptr);
    ~MenuReport();

private:
    Ui::MenuReport *ui;
};

#endif // MENUREPORT_H
