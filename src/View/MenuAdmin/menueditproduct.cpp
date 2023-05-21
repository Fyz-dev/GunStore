#include "menueditproduct.h"
#include "ui_menueditproduct.h"

const QRegularExpression MenuEditProduct::regexNull = QRegularExpression("^\\s*$");

MenuEditProduct::MenuEditProduct(MenuEditProductViewModel* menuEditProductViewModel, ConnectionHandler* connectionHandler, QWidget *parent) :
    menuEditProductViewModel(menuEditProductViewModel),
    connectionHandler(connectionHandler),
    QWidget(parent),
    ui(new Ui::MenuEditProduct)
{
    ui->setupUi(this);
    ui->comboBoxIsDelete->addItems({"Наявні товари", "Видалені товари"});
    connected();

    ui->tableViewProduct->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewProduct->setPalette(QPalette(QPalette::WindowText, Qt::white));

    menuEditProductViewModel->update(QString::number(ui->comboBoxIsDelete->currentIndex()));
    ui->tableViewProduct->setItemDelegate(menuEditProductViewModel->getDelegate());

    notification = new CenteredNotification;
}

void MenuEditProduct::modelChangedSlots(QAbstractTableModel* modelData)
{
    ui->tableViewProduct->setModel(nullptr);
    ui->tableViewProduct->setModel(modelData);
    ui->tableViewProduct->hideColumn(0);
    ui->tableViewProduct->hideColumn(9);
}

void MenuEditProduct::addCheckBoxSlots(QCheckBox* checkBox, const LayoutState& layoutName)
{
    connect(checkBox, &QCheckBox::stateChanged, this, [&](const int& state)
    {
        menuEditProductViewModel->checkBoxEnabledSlots(state, sender(), QString::number(ui->comboBoxIsDelete->currentIndex()));
    });

    switch (layoutName)
    {
    case LayoutState::CATEGORY:
        ui->frameCategorys->layout()->addWidget(checkBox);
        break;
    case LayoutState::COUNTRY:
        ui->frameCountries->layout()->addWidget(checkBox);
        break;
    case LayoutState::BRAND:
        ui->frameBrands->layout()->addWidget(checkBox);
        break;
    }
}

//Добавляем характеристики в отображение
void MenuEditProduct::addInfoProductSlots(QWidget* widget)
{
    if(widget == nullptr)
    {
        ui->verticalLayout_16->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        return;
    }

    ui->infoSelectProduct->layout()->addWidget(widget);
}

void MenuEditProduct::clearCheckBoxSlots()
{
    deleteWidget(ui->frameCategorys->layout());
    deleteWidget(ui->frameCountries->layout());
    deleteWidget(ui->frameBrands->layout());
}

void MenuEditProduct::priceFilterChangedSlots()
{
    emit priceFilterChangedSignals(ui->inputTo, ui->inputDo, QString::number(ui->comboBoxIsDelete->currentIndex()));
}

void MenuEditProduct::clearLableSlots()
{
    ui->tableViewProduct->hideColumn(0);
    ui->tableViewProduct->hideColumn(9);
    deleteWidget(ui->infoSelectProduct->layout());
}

void MenuEditProduct::deleteWidget(QLayout* layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}

void MenuEditProduct::showMessageBox()
{
    QMessageBox::information(this, tr("Увага!"), tr("Зміни внесено до бази даних."));
}

void MenuEditProduct::show()
{
    menuEditProductViewModel->update(QString::number(ui->comboBoxIsDelete->currentIndex()));
}

void MenuEditProduct::hide() {}

void MenuEditProduct::search(const QString& text)
{
    menuEditProductViewModel->updateWithSearch(text, QString::number(ui->comboBoxIsDelete->currentIndex()));
}

void MenuEditProduct::connected()
{
    //Button
    connect(ui->buttonAccept, &QPushButton::clicked, this, [&]()
    {
        menuEditProductViewModel->applyChanges();
        menuEditProductViewModel->update(QString::number(ui->comboBoxIsDelete->currentIndex()));
    });

    connect(ui->buttonAddNewProduct, &QPushButton::clicked, this, [=]()
    {
        if(canClose())
            emit openAddNewProductDialogSignals();
    });

    connect(ui->buttonDeleteProduct, &QPushButton::clicked, this, [&]()
    {
        if(!ui->tableViewProduct->currentIndex().isValid())
            return;

        if(ui->comboBoxIsDelete->currentIndex() == 0)
        {
            menuEditProductViewModel->addItemToRemove(ui->tableViewProduct->currentIndex().row());
            ui->tableViewProduct->update();
        }
        else
        {
            menuEditProductViewModel->addItemToReturn(ui->tableViewProduct->currentIndex().row());
            ui->tableViewProduct->update();
        }
    });

    connect(ui->comboBoxIsDelete, &QComboBox::currentIndexChanged, this, [&](const int& i)
    {
        if(!canClose())
        {
            ui->comboBoxIsDelete->blockSignals(true), ui->comboBoxIsDelete->setCurrentIndex(i == 1? 0 : 1), ui->comboBoxIsDelete->blockSignals(false);
            return;
        }

        if(i == 0)
        {
            menuEditProductViewModel->getDelegate()->setNewColor(QColor(255, 0, 13, 80));
            menuEditProductViewModel->getDelegate()->setNewList(menuEditProductViewModel->getListToRemove());
            ui->buttonDeleteProduct->setText("Видалити товар");
        }
        else
        {
            menuEditProductViewModel->getDelegate()->setNewColor(QColor(2, 204, 136, 80));
            menuEditProductViewModel->getDelegate()->setNewList(menuEditProductViewModel->getListToReturn());
            ui->buttonDeleteProduct->setText("Повернути товар");
        }

        menuEditProductViewModel->update(QString::number(i));
        clearLableSlots();

        ui->inputTo->setText("");
        ui->inputDo->setText("");
    });

    connect(menuEditProductViewModel, &MenuEditProductViewModel::showMessageBoxSignals, this, &MenuEditProduct::showMessageBox);
    connect(ui->inputTo, &QLineEdit::textChanged, this, &MenuEditProduct::priceFilterChangedSlots);
    connect(ui->inputDo, &QLineEdit::textChanged, this, &MenuEditProduct::priceFilterChangedSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::modelChangedSignal, this, &MenuEditProduct::modelChangedSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::addCheckBoxSignal, this, &MenuEditProduct::addCheckBoxSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::clearCheckBoxSignal, this, &MenuEditProduct::clearCheckBoxSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::addInfoProductSignal, this, &MenuEditProduct::addInfoProductSlots);
    connect(menuEditProductViewModel, &MenuEditProductViewModel::clearLableSignal, this, &MenuEditProduct::clearLableSlots);
    connect(this, &MenuEditProduct::priceFilterChangedSignals, menuEditProductViewModel, &MenuEditProductViewModel::priceFilterChangedSlots);

    connect(ui->tableViewProduct, &QTableView::clicked, this, &MenuEditProduct::selectedItem);
}

void MenuEditProduct::selectedItem(const QModelIndex& i)
{
    menuEditProductViewModel->selectedElemTableViewSlots(i, false);

    QList<QString> list = menuEditProductViewModel->getListCharact(i);
    if(list.isEmpty())
        return;

    QComboBox* comboBox = new QComboBox(this);
    QLineEdit* lineEdit = new QLineEdit(this);
    QPushButton* buttonCharact = new QPushButton(QIcon(), "Додати характеристику", this);

    comboBox->addItems(list);
    comboBox->setCurrentIndex(-1);
    lineEdit->setPlaceholderText("Введіть значення");

    addInfoProductSlots(comboBox);
    addInfoProductSlots(lineEdit);
    addInfoProductSlots(buttonCharact);

    connect(buttonCharact, &QPushButton::clicked, this, [=]()
    {
        buttonAddCharact(comboBox, lineEdit);
    });
}

void MenuEditProduct::buttonAddCharact(QComboBox* comboBox, QLineEdit* lineEdit)
{
    if(comboBox->currentIndex() == -1)
        return notification->show("Виберіть характеристику!", 2);

    if(regexNull. match(lineEdit->text()).hasMatch())
        return notification->show("Введіть значення для характеристики!", 2);

    const QModelIndex& i = ui->tableViewProduct->currentIndex();
    menuEditProductViewModel->insertCharactToBD(i.model()->index(i.row(), 0).data().toString(), comboBox->currentText(), lineEdit->text());
    selectedItem(i);
}

bool MenuEditProduct::canClose()
{
    if(!menuEditProductViewModel->isChanged())
        return true;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Увага!");
    msgBox.setText("Усі не підтверджені дані зникнуть!\nВи це підтверджуєте?");

    QPushButton* yes = msgBox.addButton("Так", QMessageBox::ActionRole);
    msgBox.addButton("Ні", QMessageBox::ActionRole);

    msgBox.exec();
    if(msgBox.clickedButton() != yes)
        return false;

    return true;
}

MenuEditProduct::~MenuEditProduct()
{
    delete notification;
    delete ui;
}
