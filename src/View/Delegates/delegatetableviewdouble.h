#ifndef DELEGATETABLEVIEWDOUBLE_H
#define DELEGATETABLEVIEWDOUBLE_H

#include <QSqlRelationalDelegate>

class DelegateTableViewDouble : public QSqlRelationalDelegate
{
public:
    DelegateTableViewDouble();

protected:
    QString displayText(const QVariant &value, const QLocale &locale) const override;
};

#endif // DELEGATETABLEVIEWDOUBLE_H
