#include "centerednotification.h"
#include "ui_centerednotification.h"
#include <QMainWindow>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>


QWidget* CenteredNotification::baseWidget = nullptr;

CenteredNotification::CenteredNotification(QWidget *parent, const QString& text, const QColor& backgroundColor) :
    QWidget(parent),
    ui(new Ui::CenteredNotification)
{
    ui->setupUi(this);
    setText(text);
    setColor(backgroundColor);

    ui->text->setWordWrap(true);
    ui->text->adjustSize();

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);

    connect(qApp, &QApplication::focusChanged, this, [=](QWidget* oldFocus, QWidget* newFocus){
        if(newFocus)
            this->raise();
    });
}

void CenteredNotification::setText(const QString& text)
{
    ui->text->setText(text);
}

void CenteredNotification::setFont(const QFont& font)
{
    ui->text->setFont(font);
}

void CenteredNotification::setBaseWidget(QWidget* basewidget)
{
    baseWidget = basewidget;
}

void CenteredNotification::setColor(const QColor& backgroundColor)
{
    this->backgroundColor = backgroundColor;
}

void CenteredNotification::show(const int& displayTimeSecond)
{
    ui->widget->setStyleSheet(QString("QWidget#widget{border-radius: 10px; background-color: %1;}").arg(backgroundColor.name(QColor::HexArgb)));
    baseWidget->installEventFilter(this);

    if(timer != nullptr)
    {
        timer->stop();
        delete timer;
    }

    if(anim != nullptr && anim->state() == QAbstractAnimation::Running)
        emit anim->finished();

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(displayTimeSecond*1000);

    connect(timer, &QTimer::timeout, this, [=]()
    {
        startAnimAsync();

        delete timer;
        timer = nullptr;
    });

    QWidget::show();

    centredTheWidget();
    timer->start();
}

void CenteredNotification::show(const QString& text, const int& displayTimeSecond)
{
    setText(text);
    show(displayTimeSecond);
}

bool CenteredNotification::eventFilter(QObject* wathed, QEvent* event)
{
    if(wathed == baseWidget && (event->type() == QEvent::Move || event->type() == QEvent::Resize))
        centredTheWidget();

    return false;
}

void CenteredNotification::startAnimAsync()
{
    (void)QtConcurrent::run([this]() {
        anim = new QPropertyAnimation(this, "windowOpacity");
        anim->setStartValue(1);
        anim->setEndValue(0);
        anim->start(QPropertyAnimation::DeleteWhenStopped);

        connect(anim, &QPropertyAnimation::finished, this, [=]()
        {
            this->setWindowOpacity(1);
            QWidget::close();
        });

        while (anim->state() == QAbstractAnimation::Running)
            QCoreApplication::processEvents();
    });
}

void CenteredNotification::centredTheWidget()
{
    //this->move(baseWidget->geometry().center().x() - this->width()/2, baseWidget->geometry().bottom() - this->geometry().height() - 20);
    this->move(baseWidget->geometry().center() - this->rect().center());
}

CenteredNotification::~CenteredNotification()
{
    baseWidget->removeEventFilter(this);
    delete ui;
}
