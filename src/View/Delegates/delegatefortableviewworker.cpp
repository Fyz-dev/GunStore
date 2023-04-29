#include "delegatefortableviewworker.h"

DelegateForTableViewWorker::DelegateForTableViewWorker(const QList<int>& listToRemove, const QSqlTableModel* model, const QColor& colorForPaint) : DelegateForTableView(listToRemove, model, colorForPaint)
{}

QWidget* DelegateForTableViewWorker::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column() == 2)
    {
        QComboBox* editor = new QComboBox(parent);\
        editor->addItems({"Адміністратор", "Продавець"});
        return editor;
    }

    if(index.column() == 5)
    {
        QComboBox* editor = new QComboBox(parent);\
        editor->addItems({"Чоловік", "Жінка"});
        return editor;
    }

    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
