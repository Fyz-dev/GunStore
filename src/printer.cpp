#include "printer.h"

Printer::Printer()
{
    printer = new QPrinter;
    printer->setPageSize(QPageSize::A4);
    printer->setFullPage(true);

    dialog = new QPrintPreviewDialog(printer);
    dialog->setWindowTitle("Предварительный просмотр печати");
}

void Printer::paintRequestedActOfSupply(QPrinter* printer, QTableView* table, const QString& FIOEmployees, const QString& FIOSupplier, const QString& sumCount, const QString& sumPrice)
{
    QPainter paint;
    paint.begin(printer);

    paint.setViewport(0, 0, printer->width(), printer->height());
    paint.setFont(QFont("Arial", 16, QFont::Bold));

    //Печатаем заголовок по центру листа
    QRectF textRect = paint.boundingRect(printer->pageRect(QPrinter::DevicePixel), Qt::AlignCenter, "Акт постачання від " + QDate::currentDate().toString("yyyy.MM.dd"));
    paint.drawText(QPointF((printer->pageRect(QPrinter::DevicePixel).width() - textRect.width()) / 2, 30), "\nАкт постачання від " + QDate::currentDate().toString("yyyy.MM.dd") + "\n");
    paint.translate(30, 50); // Сдвигаем начало координат на 50 пикселей вниз и 30 в право(чтобы был отступ)
    table->render(&paint);

    //Ставим шрифт по меньше для дальнейшей печати
    paint.setFont(QFont("Arial", 14, QFont::Normal));
    QRectF countRect = paint.boundingRect(table->rect(), Qt::AlignRight | Qt::AlignTop, "Загальна кількість: " + sumCount);
    QRectF priceRect = paint.boundingRect(table->rect(), Qt::AlignRight | Qt::AlignTop, "Загальна сума: " + sumPrice);

    //Рисуем текст, выравнивая по правому краю
    paint.drawText(countRect.topRight() + QPointF(-countRect.width(), table->rect().height()+40), "Загальна кількість: " + sumCount);
    paint.drawText(priceRect.topRight() + QPointF(-priceRect.width(), table->rect().height()+70), "Загальна сума: " + sumPrice);


    QRectF supplierNameRect = paint.boundingRect(table->rect(), Qt::AlignRight | Qt::AlignTop, FIOSupplier + "___________");
    paint.drawText(0, table->rect().height() + 170, FIOEmployees + "___________");
    paint.drawText(supplierNameRect.topRight() + QPointF(-supplierNameRect.width(), table->rect().height()+170), FIOSupplier + "___________");

    paint.setFont(QFont("Arial", 14, QFont::Bold));
    paint.drawText(0, table->rect().height() + 140, "Співробітник:");
    paint.drawText(supplierNameRect.topRight() + QPointF(-supplierNameRect.width(), table->rect().height()+140), "Постачальник:");


    paint.end();
}

void Printer::printActOfSupply(QTableView* table, const QString& FIOEmployees, const QString& FIOSupplier, const QString& sumCount, const QString& sumPrice)
{
    printer->setOutputFileName("Акт постачання - " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") + ".pdf");

    int height = table->horizontalHeader()->height();

    table->setFont(QFont("Arial", 10));
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->resizeRowsToContents();

    for(int i = 0; i < table->model()->rowCount(); ++i)
        height += table->rowHeight(i);

    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setFixedSize(printer->width()-60, height);

    connect(dialog, &QPrintPreviewDialog::paintRequested, this, [&](QPrinter *printer)
    {
        paintRequestedActOfSupply(printer, table, FIOEmployees, FIOSupplier, sumCount, sumPrice);
    });

    if(dialog->exec() == QDialog::Accepted)
        paintRequestedActOfSupply(printer, table, FIOEmployees, FIOSupplier, sumCount, sumPrice);
}

Printer::~Printer()
{
    delete printer;
    delete dialog;
}
