#include "delegatefortableviewproduct.h"
#include "qcolor.h"
#include <QSqlRelationalDelegate>

DelegateForTableViewProduct::DelegateForTableViewProduct(const QList<int>& listToRemove, const QSqlTableModel* model, const QColor colorForPaint) : DelegateForTableView(listToRemove, model, colorForPaint)
{}

QWidget* DelegateForTableViewProduct::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 8)
        return nullptr;

    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
