#include "centerednotification.h"
#include "ui_centerednotification.h"
#include <QMainWindow>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QWindow>
#include <QObject>

QWidget* CenteredNotification::baseWindow = nullptr;

CenteredNotification::CenteredNotification(const QString& text, const QColor& backgroundColor) :
    QWidget(),
    ui(new Ui::CenteredNotification)
{
    ui->setupUi(this);

    setText(text);
    setColor(backgroundColor);

    ui->text->setWordWrap(true);
    ui->text->adjustSize();

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);

    setFont(QFont("Franklin Gothic Medium", 16));
    setStyleSheet("color: white");

    connect(qApp, &QApplication::focusChanged, this, [=](QWidget* oldFocus, QWidget* newFocus)
    {
        if(!baseWindow)
            baseWindow = QApplication::activeWindow();

        if(!isInitialization)
            return;

        baseWindow->installEventFilter(this);

        connect(baseWindow->window()->windowHandle(), &QWindow::activeChanged, this, [=]()
        {
            if(timer == nullptr)
                return;

            this->raise();
//            if(baseWindow->isActiveWindow())
//            {
//                this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::ToolTip);
//                QWidget::show();
//            }
//            else
//            {
//                this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//                QWidget::show();
//            }
        });

        isInitialization = false;
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

void CenteredNotification::setColor(const QColor& backgroundColor)
{
    this->backgroundColor = backgroundColor;
}

void CenteredNotification::show(const int& displayTimeSecond)
{
    ui->widget->setStyleSheet(QString("QWidget#widget{border-radius: 10px; background-color: %1;}").arg(backgroundColor.name(QColor::HexArgb)));

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

    centredTheWidget();
    timer->start();

    QWidget::show();
}

void CenteredNotification::show(const QString& text, const int& displayTimeSecond)
{
    setText(text);
    show(displayTimeSecond);
}

void CenteredNotification::close()
{
    this->hide();

    if(timer)
    {
        delete timer;
        timer = nullptr;
    }

    if(anim)
    {
        delete anim;
        anim = nullptr;
    }
}

bool CenteredNotification::eventFilter(QObject* wathed, QEvent* event)
{
    if (event->type() == QEvent::NonClientAreaMouseButtonPress)
        this->raise();

    if(wathed == baseWindow && (event->type() == QEvent::Move || event->type() == QEvent::Resize))
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
    //this->move(baseWidow->geometry().center().x() - this->width()/2, baseWidow->geometry().top()+10);
    //this->move(baseWidow->geometry().center().x() - this->width()/2, baseWidow->geometry().bottom() - this->geometry().height() - 20);
    this->move(baseWindow->geometry().center() - this->rect().center());
}

CenteredNotification::~CenteredNotification()
{
    if(anim)
        delete anim;

    if(timer)
        delete timer;

    baseWindow->removeEventFilter(this);
    delete ui;
}
