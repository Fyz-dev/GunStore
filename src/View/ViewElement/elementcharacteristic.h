#ifndef ELEMENTCHARACTERISTIC_H
#define ELEMENTCHARACTERISTIC_H

#include <QWidget>

namespace Ui {
class ElementCharacteristic;
}

class ElementCharacteristic : public QWidget
{
    Q_OBJECT

public:
    explicit ElementCharacteristic(const QString& nameCharact, const QString& valueCharact, const int& idProductValue, bool lineEditIsReadOnly = true, QWidget *parent = nullptr);
    ~ElementCharacteristic();

    const int& getIdProductValue() const { return idProductValue; }
    const QString getValue() const;

signals:
    void changedValueSignals(ElementCharacteristic* element);

private:
    Ui::ElementCharacteristic *ui;
    int idProductValue;
};

#endif // ELEMENTCHARACTERISTIC_H
