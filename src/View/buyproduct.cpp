#include "buyproduct.h"
#include "ui_buyproduct.h"

BuyProduct::BuyProduct(BuyProductViewModel* buyProductViewModel, QWidget *parent) :
    buyProductViewModel(buyProductViewModel),
    QWidget(parent),
    ui(new Ui::BuyProduct)
{
    ui->setupUi(this);
    connected();
    buyProductViewModel->update();
}

void BuyProduct::updateComboBoxSlots(const QList<QString>& list, const QList<QString>& listSupplier)
{
    ui->comboBox->blockSignals(true);
    ui->comboBox->clear();
    ui->comboBox->addItems(list);
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->blockSignals(false);

    ui->comboBoxSupplier->clear();
    ui->comboBoxSupplier->addItems(listSupplier);
    ui->comboBoxSupplier->setCurrentIndex(-1);
}

void BuyProduct::addElemntByView(ElementBuyProduct* element)
{
    qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout())->insertWidget(0, element);
}

void BuyProduct::updateSumInfoSlots(const int& sumCount, const double& sumPrice)
{
    ui->sumCount->setText(QString::number(sumCount) + " од.");
    ui->sumPrice->setText(QString::number(sumPrice, 'f', 2) + " грн.");
}

void BuyProduct::connected()
{
    connect(buyProductViewModel, &BuyProductViewModel::messageBoxShowSignals, this, &BuyProduct::messageBoxShow);
    connect(buyProductViewModel, &BuyProductViewModel::updateSumInfoSignals, this, &BuyProduct::updateSumInfoSlots);
    connect(buyProductViewModel, &BuyProductViewModel::updateComboBoxSignals, this, &BuyProduct::updateComboBoxSlots);
    connect(buyProductViewModel, &BuyProductViewModel::addElemntByViewSignals, this, &BuyProduct::addElemntByView);
    connect(ui->comboBox, &QComboBox::currentIndexChanged, buyProductViewModel, &BuyProductViewModel::changedComboBoxSlots);

    connect(ui->buttonPurchaseProduct, &QPushButton::clicked, this, [&]()
    {
        if(ui->comboBoxSupplier->currentIndex() == -1)
        {
            QMessageBox::information(this, "Увага!", "Виберіть постачальника!");
            return;
        }

        buyProductViewModel->buyProducts(ui->comboBox->currentText());
    });

    connect(buyProductViewModel, &BuyProductViewModel::addComboBoxSignals, this, [=](const QString& itemName)
    {
        ui->comboBox->blockSignals(true);
        ui->comboBox->addItem(itemName);
        ui->comboBox->setCurrentIndex(-1);
        ui->comboBox->blockSignals(false);
    });
}

void BuyProduct::messageBoxShow()
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setText("Операція пройшла успішно!\nКуплено товару на суму: " + ui->sumPrice->text());
    msgBox->addButton(tr("Ок"), QMessageBox::ActionRole);
    QPushButton* print = msgBox->addButton(tr("Друк"), QMessageBox::ActionRole);

    msgBox->exec();
    if(qobject_cast<QPushButton*>(msgBox->clickedButton()) == print)
        buyProductViewModel->printReport(ui->sumCount->text(), ui->sumPrice->text());

    buyProductViewModel->update();
}

BuyProduct::~BuyProduct()
{
    delete ui;
}
