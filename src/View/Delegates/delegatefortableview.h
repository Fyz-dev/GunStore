#ifndef DELEGATEFORTABLEVIEW_H
#define DELEGATEFORTABLEVIEW_H

#include "delegatetableviewdouble.h"
#include <QPainter>

class DelegateForTableView : public DelegateTableViewDouble
{
public:
    DelegateForTableView(QList<int>& list, const QSqlTableModel* model, const QColor& colorForPaint);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setNewColor(const QColor& colorForPaint) { this->colorForPaint = colorForPaint; }
    void setNewList(QList<int>& list) { this->list = &list; }

private:
    QList<int>* list;
    QColor colorForPaint;
    const QSqlTableModel* model;
};

#endif // DELEGATEFORTABLEVIEW_H
