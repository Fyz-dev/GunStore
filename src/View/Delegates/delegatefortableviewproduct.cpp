#include "delegatefortableviewproduct.h"
#include "qcolor.h"
#include <QSqlRelationalDelegate>

DelegateForTableViewProduct::DelegateForTableViewProduct(QList<int>& listToRemove, const QSqlTableModel* model, const QColor colorForPaint) : DelegateForTableView(listToRemove, model, colorForPaint)
{}

QWidget* DelegateForTableViewProduct::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 8 || index.column() == 3)
        return nullptr;

    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
