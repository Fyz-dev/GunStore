#ifndef PRINTER_H
#define PRINTER_H

#include "productmodel.h"

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
    Printer(QPageSize pageSize = QPageSize::A4);
    ~Printer();
    void printActOfSupply(QTableView* table, const QString& FIOEmployees, const QString& FIOSupplier, const QString& sumCount, const QString& sumPrice);
    void printCheque(QHash<int, int>& listProduct, ProductModel* model, const QString& dateTime);

private:
    void paintRequestedActOfSupply(QPrinter* printer, QTableView* table, const QString& FIOEmployees, const QString& FIOSupplier, const QString& sumCount, const QString& sumPrice);
    void paintRequestedCheque(QHash<int, int>& listProduct, ProductModel* model, const QString& dateTime);

private:
   QPrinter* printer;
   QPrintPreviewDialog* dialog;
};

#endif // PRINTER_H
