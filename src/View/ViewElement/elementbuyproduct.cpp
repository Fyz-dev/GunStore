#include "elementbuyproduct.h"
#include "ui_elementbuyproduct.h"

ElementBuyProduct::ElementBuyProduct(const QSqlTableModel* model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementBuyProduct)
{
    ui->setupUi(this);

    ui->labelNameProduct->setText(nameProduct = model->index(0, 0).data().toString());
    ui->productCount->setText(model->index(0, 1).data().toString());
    ui->productBrand->setText(model->index(0, 2).data().toString());
    ui->productWeight->setText(model->index(0, 3).data().toString());
    ui->productPackage->setText(model->index(0, 4).data().toString());
    ui->productCountry->setText(model->index(0, 5).data().toString());
    ui->categoryName->setText(model->index(0, 6).data().toString());
    price = (model->index(0, 7).data().toDouble() - model->index(0, 7).data().toFloat()/100 * 30);

    connected();
    setCount(1);
}

void ElementBuyProduct::setCount(int count)
{
    this->count = count;
    ui->inputProductCount->setText(QString::number(this->count));
}

void ElementBuyProduct::connected()
{
    connect(ui->buttonDelete, &QPushButton::clicked, this, [&]()
    {
        emit deleteMe(this);
    });

    connect(ui->inputProductCount, &QLineEdit::textChanged, this, [&](const QString& str)
    {
        static const QRegularExpression regex("^[0-9]+$");
        if(!regex.match(str).hasMatch())
            return ui->inputProductCount->setText("1");

        if(str.toInt() == 0)
        {
            QMessageBox::warning(this, tr("Помилка!"), tr("Значення має бути більше одиниці!"));
            return ui->inputProductCount->setText("1");
        }

        count = str.toInt();
        sumPrice = count * price;
        ui->sumPrice->setText(QString::number(sumPrice, 'f', 2) + " грн.");
        emit changedCountPriceSignals();
    });

    connect(ui->buttonCountAdd, &QPushButton::clicked, this, [&]()
    {
        setCount(count + 1);
    });

    connect(ui->buttonCountDec, &QPushButton::clicked, this, [&]()
    {
        if(count > 1)
            setCount(count - 1);
    });
}

QString ElementBuyProduct::getBrand() { return ui->productBrand->text(); }

const QString& ElementBuyProduct::getNameProduct()
{
    return nameProduct;
}

ElementBuyProduct::~ElementBuyProduct()
{
    delete ui;
}
