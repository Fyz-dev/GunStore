#include "ordering.h"
#include "addbuyer.h"
#include "formwithbuttonback.h"
#include "formforempty.h"
#include "ui_ordering.h"
#include <QMainWindow>

Ordering::Ordering(QHash<int, int>& listProduct, ConnectionHandler* connectionHandler, QWidget *parent) :
    QDialog(parent),
    parent(parent),
    listProduct(listProduct),
    ui(new Ui::Ordering)
{
    ui->setupUi(this);
    productModel = new ProductModel(connectionHandler);
    filter = new Filter;

    QStringList list;
    for (QHash<int, int>::key_iterator var = listProduct.keyBegin(); var != listProduct.keyEnd(); ++var)
        list.append(QString::number(*var));

    productModel->updateModel("product", filter->getFilterForList(list, "id_product"), 8, QSqlRelation("category", "id_category", "c_name"));
    QSqlRelationalTableModel* model = productModel->getModelData();


    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount()+3);

    // Заполнение таблицы данными из модели
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidget->setItem(row, col, item);
        }
    }

    // Установка заголовков таблицы
    for (int col = 0; col < model->columnCount(); ++col)
        ui->tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));

    //Заполняю количество, цену и кнопка для удаления
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(QString::number(listProduct.value(model->index(row, 0).data().toInt()))));
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(QString::number(model->index(row, 2).data().toInt()*listProduct.value(model->index(row, 0).data().toDouble()), 'f', 2)));

        QPushButton* button = new QPushButton;
        connect(button, &QPushButton::clicked, this, &Ordering::deleteProduct);

        button->setIcon(QIcon(":/WhiteIcon/images/icon-clear.png"));
        button->setStyleSheet("QPushButton{ border-radius: 15px; background-color: transparent;}QPushButton::hover{background-color: red;}");
        ui->tableWidget->setCellWidget(row, 11, button);
    }

    //Установка заголовков для количества, цени и кнопки для удаления
    ui->tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("Кількість (од.)"));
    ui->tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("Сума (грн.)"));
    ui->tableWidget->setHorizontalHeaderItem(11, new QTableWidgetItem(""));

    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(11, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(11, 24);

    ui->tableWidget->setEditTriggers(QHeaderView::NoEditTriggers);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->hideColumn(3);

    updateSumAndCount();

    connect(ui->buttonNext, &QPushButton::clicked, this, &Ordering::next);
}

void Ordering::updateSumAndCount()
{
    double sum = 0;
    int count = 0;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        sum += ui->tableWidget->item(row, 10)->text().toDouble();
        count += ui->tableWidget->item(row, 9)->text().toInt();
    }

    ui->sumPrice->setText(QString::number(sum, 'f', 2));
    ui->sumCount->setText(QString::number(count));
}

void Ordering::deleteProduct()
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
        if(ui->tableWidget->cellWidget(row, 11) == sender())
        {
            listProduct.remove(ui->tableWidget->item(row, 0)->text().toInt());
            ui->tableWidget->removeRow(row);
            updateSumAndCount();
        }

    if(listProduct.isEmpty())
    {
        FormWithButtonBack::clearStack();
        FormWithButtonBack::pushToView({new FormForEmpty});
    }
}

void Ordering::next()
{
    FormWithButtonBack::pushToView({new AddBuyer(productModel, listProduct, this)});
}

Ordering::~Ordering()
{
    delete filter;
    delete productModel;
    delete ui;
}
