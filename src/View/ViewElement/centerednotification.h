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
    explicit CenteredNotification(const QString& text = "", const QColor& backgroundColor = QColor(64,69,75, 245));
    ~CenteredNotification();

    //Method
public:
    void show(const int& displayTimeSecond);
    void show(const QString& text, const int& displayTimeSecond);
    void close();

    //SET
    void setText(const QString& text);
    void setFont(const QFont& font);
    void setColor(const QColor& backgroundColor);

protected:
    void show();
    bool eventFilter(QObject* watched, QEvent* event) override;
    virtual void startAnimAsync();

private:
    void centredTheWidget();

private:
    Ui::CenteredNotification *ui;

    bool isInitialization = true;
    QColor backgroundColor;
    QPropertyAnimation* anim = nullptr;
    QTimer* timer = nullptr;

    static QWidget* baseWindow;
};

#endif // CENTEREDNOTIFICATION_H
