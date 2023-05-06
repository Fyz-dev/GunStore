#ifndef DELEGATEFORTABLEVIEWWORKER_H
#define DELEGATEFORTABLEVIEWWORKER_H

#include "delegatefortableview.h"

class DelegateForTableViewWorker : public DelegateForTableView
{
public:
    DelegateForTableViewWorker(QList<int>& listToRemove, const QSqlTableModel* model, const QColor& colorForPaint);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // DELEGATEFORTABLEVIEWWORKER_H
