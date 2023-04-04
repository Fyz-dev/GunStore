#ifndef ADDNEWSUPPLIER_H
#define ADDNEWSUPPLIER_H

#include <QDialog>

namespace Ui {
class AddNewSupplier;
}

class AddNewSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewSupplier(QWidget *parent = nullptr);
    ~AddNewSupplier();

private:
    Ui::AddNewSupplier *ui;
};

#endif // ADDNEWSUPPLIER_H
