#ifndef INFOEMPLOYEES_H
#define INFOEMPLOYEES_H

#include "employeesmodel.h"
#include "centerednotification.h"

#include <QWidget>

namespace Ui {
class InfoEmployees;
}

class InfoEmployees : public QWidget
{
    Q_OBJECT

public:
    explicit InfoEmployees(const QString& idEmployees, EmployeesModel* model, QWidget *parent = nullptr);
    ~InfoEmployees();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void change();

private:
    void update();

private:
    Ui::InfoEmployees *ui;
    const QString& idEmployees;
    QString lastText;
    QString lastDate;
    QString position;
    int idLastGender;

    EmployeesModel* model;
    CenteredNotification* notification;
    static const QRegularExpression regexNull;
};

#endif // INFOEMPLOYEES_H
