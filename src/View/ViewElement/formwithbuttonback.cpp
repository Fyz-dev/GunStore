#include "formwithbuttonback.h"
#include "ui_formwithbuttonback.h"

#include <QMainWindow>

FormWithButtonBack* FormWithButtonBack::instance = nullptr;
QLayout* FormWithButtonBack::baseCentalWidgetWindow = nullptr;
QWidget* FormWithButtonBack::thisWidget = nullptr;
QStack<QList<QWidget*>> FormWithButtonBack::stack;

FormWithButtonBack* FormWithButtonBack::getInstance(QLayout *baseCentalWidgetWindow)
{
    if (!instance)
        instance = new FormWithButtonBack(baseCentalWidgetWindow);

    return instance;
}

FormWithButtonBack::FormWithButtonBack(QLayout *baseCentalWidgetWindow) :
    QWidget(),
    ui(new Ui::FormWithButtonBack)
{
    ui->setupUi(this);
    ui->widget->setLayout(new QHBoxLayout);

    this->baseCentalWidgetWindow = baseCentalWidgetWindow;
    thisWidget = ui->widget;

    connect(ui->buttonBack, &QPushButton::clicked, this, &FormWithButtonBack::closeMe);
}

void FormWithButtonBack::pushToView(QList<QWidget*> newDisplay)
{
    if(stack.empty())
    {
        QList<QWidget*> list;
        for (int i = 0; i < baseCentalWidgetWindow->count(); ++i)
            list.append(baseCentalWidgetWindow->itemAt(i)->widget());

        stack.push(list);

        baseCentalWidgetWindow->addWidget(instance);
        instance->show();
    }

    for (QWidget* item : stack.last())
        item->hide();

    for (QWidget* item : newDisplay)
        thisWidget->layout()->addWidget(item);

    stack.push(newDisplay);
}

void FormWithButtonBack::clearStack()
{
    for (int i= 0; i < stack.count(); ++i)
        for (QWidget* item : stack.pop())
                delete item;

    for (QWidget* item : stack.last())
        item->show();

    baseCentalWidgetWindow->removeWidget(instance);
    instance->hide();
    stack.pop();
}

void FormWithButtonBack::popView()
{
    for (QWidget* item : stack.pop())
        delete item;

    for (QWidget* item : stack.last())
        item->show();


    if(stack.count() == 1)
    {
        baseCentalWidgetWindow->removeWidget(instance);
        instance->hide();
        stack.pop();
    }
}

void FormWithButtonBack::closeMe()
{
    popView();
}

FormWithButtonBack::~FormWithButtonBack()
{
    instance = nullptr;
    delete ui;
}
