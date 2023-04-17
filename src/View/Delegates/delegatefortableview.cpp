#include "delegatefortableview.h"

DelegateForTableView::DelegateForTableView(const QList<int>& listToRemove, const QSqlTableModel* model) : listToRemove(listToRemove),
    model(model)
{}

void DelegateForTableView::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSqlRelationalDelegate::paint(painter, option, index);

    if(listToRemove.contains(model->data(model->index(index.row(), 0)).toInt()))
    {
        painter->setBrush(QColor(204, 0, 13));
        painter->setPen(Qt::transparent);
        painter->drawRect(option.rect);

        QTextOption textOption;
        textOption.setAlignment(Qt::AlignVCenter);
        textOption.setWrapMode(QTextOption::NoWrap);
        painter->setPen(Qt::white);

        QRect textRect = option.rect.adjusted(4, 0, -4, 0);
        QString elidedText = QFontMetrics(option.font).elidedText(index.data().toString(), Qt::ElideRight, textRect.width());
        painter->drawText(textRect, elidedText, textOption);
    }
}
