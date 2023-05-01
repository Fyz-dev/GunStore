#ifndef CENTEREDNOTIFICATION_H
#define CENTEREDNOTIFICATION_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class CenteredNotification;
}

class CenteredNotification : public QWidget
{
    Q_OBJECT

    //Construct and Destruct
public:
    explicit CenteredNotification(QWidget *parent = nullptr, const QString& text = "", const QColor& backgroundColor = QColor(64,69,75, 245));
    ~CenteredNotification();

    //Method
public:
    void show(const int& displayTimeSecond);
    void show(const QString& text, const int& displayTimeSecond);

    //SET
    void setText(const QString& text);
    void setFont(const QFont& font);
    void setColor(const QColor& backgroundColor);
    static void setBaseWidget(QWidget* baseWidget);

protected:
    void show();
    bool eventFilter(QObject* watched, QEvent* event) override;
    virtual void startAnimAsync();

private:
    void centredTheWidget();

private:
    Ui::CenteredNotification *ui;

    QColor backgroundColor;
    QPropertyAnimation* anim = nullptr;
    QTimer* timer = nullptr;

    static QWidget* baseWidget;
};

#endif // CENTEREDNOTIFICATION_H
