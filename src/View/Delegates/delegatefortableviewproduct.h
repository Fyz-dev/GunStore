#ifndef DELEGATEFORTABLEVIEWPRODUCT_H
#define DELEGATEFORTABLEVIEWPRODUCT_H

#include "delegatefortableview.h"

class DelegateForTableViewProduct : public DelegateForTableView
{
public:
    DelegateForTableViewProduct(const QList<int>& listToRemove, const QSqlTableModel* model, const QColor colorForPaint);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DELEGATEFORTABLEVIEWPRODUCT_H
