#include "printer.h"
#include "filter.h"

#include <QFontMetrics>

Printer::Printer(QPageSize pageSize)
{
    printer = new QPrinter;
    printer->setPageSize(pageSize);
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

void Printer::paintRequestedCheque(QHash<int, int>& listProduct, ProductModel* model, const QString& dateTime)
{
    printer->setPageSize(QPageSize(QSizeF(QPageSize(QPageSize::B7).size(QPageSize::Millimeter).width(), 60 + listProduct.count() * 5.5), QPageSize::Millimeter));
    int widthPrinter = printer->width();
    QFont fontDelimeter("Arial", 8, QFont::Normal);
    QFontMetrics fm(fontDelimeter);
    QString delimeter((widthPrinter-30) / fm.horizontalAdvance("-"), '-');

    QPainter paint;
    paint.begin(printer);

    paint.setViewport(0, 0, widthPrinter, printer->height());
    paint.setFont(QFont("Arial", 12, QFont::Bold));

    //paint.drawRect(0, 0, printer->width(), printer->height());
    paint.drawText(QRect(0, 0, widthPrinter, 30), Qt::AlignCenter, "GunStore");
    paint.setFont(fontDelimeter);
    paint.drawText(QRect(0, 0, widthPrinter, 70), Qt::AlignCenter, "Ласкаво просимо!");
    paint.drawText(QRect(0, 0, widthPrinter, 150), Qt::AlignCenter, delimeter);

    paint.setFont(QFont("Arial", 8, QFont::Normal));
    paint.drawText(QRect(0, 0, widthPrinter, 130), Qt::AlignCenter, "Дата: " + QDateTime::fromString(dateTime, "yyyy-MM-ddTh:mm:ss.zzz").toString("yyyy-MM-dd") + "      Час: " + QDateTime::fromString(dateTime, "yyyy-MM-ddTh:mm:ss.zzz").toString("h:mm:ss"));

    //Печать товаров
    int heightForProduct = 190;
    double sumPrice = 0;
    for (QHash<int, int>::key_iterator key = listProduct.keyBegin(); key != listProduct.keyEnd(); ++key, heightForProduct += 40)
    {
        QString keyR = QString::number(*key);
        QString valueR = QString::number(listProduct.value(*key));
        QString price = model->getOneCell(QString("select sum(p_priceOne*%1) from product where id_product = %2").arg(valueR,keyR));
        sumPrice += price.toDouble();
        paint.drawText(QRect(15, 0, widthPrinter, heightForProduct), Qt::AlignLeft | Qt::AlignVCenter, model->getOneCell(QString("select p_name from product where id_product = %1").arg(keyR)) + " x " + valueR);
        paint.drawText(QRect(0, 0, widthPrinter-15, heightForProduct), Qt::AlignRight | Qt::AlignVCenter, price + "₴");
    }
    paint.drawText(QRect(0, 0, widthPrinter, heightForProduct), Qt::AlignCenter, delimeter);

    //Сумма
    paint.drawText(QRect(15, 0, widthPrinter, heightForProduct += 40), Qt::AlignLeft | Qt::AlignVCenter, "Сума");
    paint.drawText(QRect(0, 0, widthPrinter-15, heightForProduct), Qt::AlignRight | Qt::AlignVCenter, QString::number(sumPrice, 'f', 2) + "₴");

    paint.drawText(QRect(15, 0, widthPrinter, heightForProduct += 30), Qt::AlignLeft | Qt::AlignVCenter, "ПДВ 7.00%");
    paint.drawText(QRect(0, 0, widthPrinter-15, heightForProduct), Qt::AlignRight | Qt::AlignVCenter, QString::number(sumPrice/100*7, 'f', 2) + "₴");

    paint.drawText(QRect(0, 0, widthPrinter, heightForProduct += 40), Qt::AlignCenter, delimeter);

    paint.drawText(QRect(15, 0, widthPrinter, heightForProduct += 40), Qt::AlignLeft | Qt::AlignVCenter, "До сплати");
    paint.drawText(QRect(0, 0, widthPrinter-15, heightForProduct), Qt::AlignRight | Qt::AlignVCenter, QString::number(sumPrice, 'f', 2) + "₴");

    paint.drawText(QRect(0, 0, widthPrinter, heightForProduct += 60), Qt::AlignCenter, "Дякую за покупку!");
    paint.drawText(QRect(0, 0, widthPrinter, heightForProduct + 30), Qt::AlignCenter, "Слава Україні!");

    paint.end();
}

void Printer::printCheque(QHash<int, int>& listProduct, ProductModel* model, const QString& dateTime)
{
    printer->setOutputFileName("Чек - " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") + ".pdf");

    connect(dialog, &QPrintPreviewDialog::paintRequested, this, [&](QPrinter *printer) { paintRequestedCheque(listProduct, model, dateTime); });

    if(dialog->exec() == QDialog::Accepted)
        paintRequestedCheque(listProduct, model, dateTime);

}

Printer::~Printer()
{
    delete printer;
    delete dialog;
}
