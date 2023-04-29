#ifndef DELEGATEFORTABLEVIEW_H
#define DELEGATEFORTABLEVIEW_H

#include <QSqlRelationalDelegate>
#include <QPainter>

class DelegateForTableView : public QSqlRelationalDelegate
{
public:
    DelegateForTableView(const QList<int>& listToRemove, const QSqlTableModel* model, const QColor colorForPaint);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    const QList<int>& list;
    const QSqlTableModel* model;
    const QColor colorForPaint;
};

#endif // DELEGATEFORTABLEVIEW_H
