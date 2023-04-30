#ifndef FILTER_H
#define FILTER_H

#include <QLineEdit>
#include <QRegularExpression>
#include <QCheckBox>

class Filter
{

public:
    Filter();

public:
    QString priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo);
    QString checkBoxEnabled(const int& state, QObject* checkBox);
    QString getFilterForList(const QStringList& list, const QString& nameColumCopare);

private:
    QString updateModelByFilter();

private:
    QList<QObject*> listCheckBoxEnabled;
    QString priceTo, priceDo;
};

#endif // FILTER_H
