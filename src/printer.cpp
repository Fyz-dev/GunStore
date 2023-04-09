#include "printer.h"

Printer::Printer()
{
    printer = new QPrinter;
    printer->setPageSize(QPageSize::A4);
    printer->setFullPage(true);

    dialog = new QPrintPreviewDialog(printer);
    dialog->setWindowTitle("Предварительный просмотр печати");
}

void Printer::paintRequestedActOfSupply(QPrinter* printer, QTableView* table, const QString& sumCount, const QString& sumPrice)
{
    QPainter paint;
    paint.begin(printer);

    paint.setViewport(0, 0, printer->width(), printer->height());

    paint.setFont(QFont("Arial", 16, QFont::Bold));
    QRectF textRect = paint.boundingRect(printer->pageRect(QPrinter::DevicePixel), Qt::AlignCenter,
                                         "Акт постачання від " + QDate::currentDate().toString("yyyy.MM.dd"));

    paint.drawText(QPointF((printer->pageRect(QPrinter::DevicePixel).width() - textRect.width()) / 2, 20),
                   "\nАкт постачання від " + QDate::currentDate().toString("yyyy.MM.dd") + "\n");

    paint.translate(0, 50); // Сдвигаем начало координат на 50 пикселей вниз
    table->render(&paint);

    paint.setFont(QFont("Arial", 14, QFont::Normal));
    paint.drawText(0, table->rect().height() + 70, "Співробітник Підпис___________");
    paint.drawText(0, table->rect().height() + 100, "Постачальник Підпис___________");
    paint.drawText(table->rect().width()-300, table->rect().height() + 70, "Загальна кількість: " + sumCount + " од.");
    paint.drawText(table->rect().width()-300, table->rect().height() + 100, "Загальна сума: " + sumPrice);

    paint.end();
}

void Printer::printActOfSupply(QTableView* table, const QString& sumCount, const QString& sumPrice)
{
    printer->setOutputFileName("Акт постачання - " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") + ".pdf");

    table->setMinimumSize(printer->width(), 0);
    table->setFont(QFont("Arial", 10));
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(dialog, &QPrintPreviewDialog::paintRequested, this, [&](QPrinter *printer)
    {
        paintRequestedActOfSupply(printer, table, sumCount, sumPrice);
    });

    if(dialog->exec() == QDialog::Accepted)
        paintRequestedActOfSupply(printer, table, sumCount, sumPrice);
}

Printer::~Printer()
{
    delete printer;
    delete dialog;
}
