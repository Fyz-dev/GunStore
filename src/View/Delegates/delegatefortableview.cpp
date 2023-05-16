#include "delegatefortableview.h"

DelegateForTableView::DelegateForTableView(QList<int>& list, const QSqlTableModel* model, const QColor& colorForPaint) : list(&list),
    model(model),
    colorForPaint(colorForPaint)
{}

void DelegateForTableView::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(list->contains(model->data(model->index(index.row(), 0)).toInt()))
    {
        painter->setBrush(colorForPaint);
        painter->setPen(Qt::transparent);
        painter->drawRect(option.rect);
    }
    QSqlRelationalDelegate::paint(painter, option, index);
}

QString DelegateForTableView::displayText(const QVariant &value, const QLocale &locale) const
{
    if(value.typeId() == QMetaType::Double)
    {
        QString newValue = QString::number(value.toDouble(), 'f', 2);
        newValue.replace('.', ',');
        return QSqlRelationalDelegate::displayText(newValue, locale);
    }

    return QSqlRelationalDelegate::displayText(value, locale);
}
