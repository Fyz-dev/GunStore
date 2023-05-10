#include "menureport.h"
#include "ui_menureport.h"
#include <QChartView>
#include <QSplineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDateTime>
#include <QAreaSeries>

MenuReport::MenuReport(ProductModel* productModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuReport)
{
    ui->setupUi(this);
    ui->chartView->chart()->setTheme(QChart::ChartThemeDark);
    ui->chartView->chart()->setBackgroundBrush(QBrush(QColor(32, 33, 36)));

    productModel->updateModelViaQuery("select date(date_time), sum(p_priceOne*listP_count) from listproduct join product using(id_product) join sales using(id_sales) group by 1 order by 1");
    QSqlRelationalTableModel* model = productModel->getModelData();



    //Линия для продаж
    QSplineSeries* seriesSales = new QSplineSeries(this);
    seriesSales->setName(" - Продаж");

    double sumSales = 0;

    for (int i = 0; i < model->rowCount(); ++i)
    {
        seriesSales->append(QDateTime::fromString(model->index(i, 0).data().toString(), "yyyy-MM-dd").toMSecsSinceEpoch(), model->index(i, 1).data().toDouble());
        sumSales += model->index(i, 1).data().toDouble();
    }

    double maxSales = productModel->getOneCell("select sum(p_priceOne*listP_count) from listproduct join product using(id_product) join sales using(id_sales) group by date(date_time) order by 1 desc limit 1").toDouble();

    QPen pen = seriesSales->pen();
    pen.setWidth(3);
    pen.setColor(QColor(1, 176, 117));
    seriesSales->setPen(pen);



    //Линия для закупок
    QSplineSeries* seriesBuy = new QSplineSeries(this);
    seriesBuy->setName(" - Закупки");

    double sumBuy = 0;

    productModel->updateModelViaQuery("select waybillDate, sum(listS_priceCount*listS_count) from listsupply join waybill using(id_waybill) group by 1 order by 1");
    for (int i = 0; i < model->rowCount(); ++i)
    {
        seriesBuy->append(QDateTime::fromString(model->index(i, 0).data().toString(), "yyyy-MM-dd").toMSecsSinceEpoch(), model->index(i, 1).data().toDouble());
        sumBuy += model->index(i, 1).data().toDouble();
    }

    double maxBuy = productModel->getOneCell("select sum(listS_priceCount*listS_count) from listsupply join waybill using(id_waybill) group by 1 order by 1 desc limit 1").toDouble();
    double max = maxSales > maxBuy ? maxSales : maxBuy;

    pen.setWidth(3);
    pen.setColor(QColor(153, 0, 0));
    seriesBuy->setPen(pen);



    ui->salesSum->setText(QString::number(sumSales, 'f', 2) + " грн.");
    ui->buySum->setText(QString::number(sumBuy, 'f', 2) + " грн.");

    // Создание осей X и Y
    QDateTimeAxis *axisX = new QDateTimeAxis(this);
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTitleText("Дата");

    QValueAxis *axisY = new QValueAxis(this);
    axisY->setLabelFormat("%.0f");
    axisY->setMax(qCeil(max+max/100*5));

    // Создание графика и добавление данных
    ui->chartView->chart()->addSeries(seriesBuy);
    ui->chartView->chart()->addSeries(seriesSales);
    ui->chartView->chart()->addAxis(axisX, Qt::AlignBottom);
    ui->chartView->chart()->addAxis(axisY, Qt::AlignLeft);
    ui->chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    ui->chartView->chart()->legend()->setMarkerShape(QLegend::MarkerShapeCircle);
    seriesSales->attachAxis(axisX);
    seriesSales->attachAxis(axisY);

    ui->buttonReportPrint->hide();
}

MenuReport::~MenuReport()
{
    delete ui;
}
