#include "delegatetableviewdouble.h"

DelegateTableViewDouble::DelegateTableViewDouble()
{

}

QString DelegateTableViewDouble::displayText(const QVariant &value, const QLocale &locale) const
{
    if(value.typeId() == QMetaType::Double)
    {
        QString newValue = QString::number(value.toDouble(), 'f', 2);
        newValue.replace('.', ',');
        return QSqlRelationalDelegate::displayText(newValue, locale);
    }

    return QSqlRelationalDelegate::displayText(value, locale);
}
