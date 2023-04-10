#include "mainmenuviewmodel.h"

MainMenuViewModel::MainMenuViewModel(ProductModel* productModel) : BaseViewModel("select p_name as 'Назва', p_priceOne as 'Ціна(грн.)', p_count as 'Кількість(шт.)', p_brand as 'Бренд', p_weight as 'Вес(г.)',p_package as 'Упаковка', p_country as 'Країна', c_name as 'Категорія' from product join category using(id_category)")
    , productModel(productModel)
{
    filter = new Filter;
}

void MainMenuViewModel::update()
{
    if(!productModel->updateModel(standartRequest))
        return;

    emit modelChangedSignal(productModel->getModelData());

    productModel->updateListFilter();
    emit clearCheckBoxSignal();

    addCheckBox(productModel->createCheckBox(productModel->getListCategory()), LayoutState::CATEGORY);
    addCheckBox(productModel->createCheckBox(productModel->getListCountry()), LayoutState::COUNTRY);
    addCheckBox(productModel->createCheckBox(productModel->getListBrand()), LayoutState::BRAND);
}

void MainMenuViewModel::priceFilterChangedSlots(QLineEdit* inputTo, QLineEdit* inputDo)
{
    productModel->updateModel(standartRequest + filter->priceFilterChangedSlots(inputTo, inputDo));
    emit clearLableSignal();
}

void MainMenuViewModel::checkBoxEnabledSlots(const int& state)
{
    productModel->updateModel(standartRequest + filter->checkBoxEnabled(state, sender()));
    emit clearLableSignal();
}

void MainMenuViewModel::selectedElemTableViewSlots(const QModelIndex& i)
{
    emit clearLableSignal();
    QHash<QLabel*, QLineEdit*>* list = productModel->createElementForDispleyCharact("call getCharacteristicForProduct('" +
                                                                                   i.model()->data(i.model()->index(i.row(), 0)).toString() +"')");

    if(!list)
        return;

    emit clearLableSignal();
    for (QLineEdit*& value : (*list))
        emit addInfoProductSignal(list->key(value), value);

    emit addInfoProductSignal();

    delete list;
}

void MainMenuViewModel::addCheckBox(const QList<QCheckBox*>& listCheckBox, const LayoutState& layoutName)
{
    for (QCheckBox* checkBox : listCheckBox) {
        connect(checkBox, &QCheckBox::stateChanged, this, &MainMenuViewModel::checkBoxEnabledSlots);
        emit addCheckBoxSignal(checkBox, layoutName);
    }
}

MainMenuViewModel::~MainMenuViewModel()
{
    delete filter;
}
