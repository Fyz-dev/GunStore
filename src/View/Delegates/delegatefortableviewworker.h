#ifndef DELEGATEFORTABLEVIEWWORKER_H
#define DELEGATEFORTABLEVIEWWORKER_H

#include "delegatefortableview.h"

class DelegateForTableViewWorker : public DelegateForTableView
{
public:
    DelegateForTableViewWorker(const QList<int>& listToRemove, const QSqlTableModel* model);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // DELEGATEFORTABLEVIEWWORKER_H
