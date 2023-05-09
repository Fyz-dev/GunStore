#ifndef PRINTER_H
#define PRINTER_H

#include <QDateTime>
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QHeaderView>
#include <QTableView>

class Printer : public QObject
{
    Q_OBJECT
public:
    Printer();
    ~Printer();
    void printActOfSupply(QTableView* table, const QString& FIOEmployees, const QString& FIOSupplier, const QString& sumCount, const QString& sumPrice);

private:
    void paintRequestedActOfSupply(QPrinter* printer, QTableView* table, const QString& FIOEmployees, const QString& FIOSupplier, const QString& sumCount, const QString& sumPrice);

private:
   QPrinter* printer;
   QPrintPreviewDialog* dialog;
};

#endif // PRINTER_H
