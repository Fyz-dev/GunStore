#include "productmodel.h"

ProductModel::ProductModel(QSqlDatabase* db) : BaseModel(db)
{}

void ProductModel::updateListFilter()
{
    updateList(listCategory, "select c_name from product join category using(id_category) group by id_category");
    updateList(listCountry, "select p_country from product group by p_country");
    updateList(listBrand, "select p_brand from product group by p_brand");
}

void ProductModel::updateList(QList<QString>& list, QString request)
{
   QSqlQuery* query = select(request);

   if(query == nullptr)
       return;

   list.clear();
   while(query->next())
       list.append(query->value(0).toString());

   delete query;
}

QHash<QLabel*, QLineEdit*>* ProductModel::createElementForDispleyCharact(QString request, bool lineEditIsReadOnly)
{
    QSqlQuery* query = select(request);
    QHash<QLabel*, QLineEdit*>* listCharacter;

    if(query == nullptr)
        return nullptr;

    listCharacter = new QHash<QLabel*, QLineEdit*>;
    while(query->next())
    {
        QLabel* label = new QLabel;
        label->setText(query->value(0).toString() + ":");
        label->setAlignment(Qt::AlignLeft);

        QLineEdit* lineEdit = new QLineEdit;
        lineEdit->setText(query->value(1).toString());
        lineEdit->setReadOnly(lineEditIsReadOnly);
        listCharacter->insert(label, lineEdit);
    }

    delete query;
    return listCharacter;
}

QList<QCheckBox*> ProductModel::createCheckBox(const QList<QString>& list)
{
    QList<QCheckBox*> listCheckBox;

    for(const QString& value : list)
    {
        QCheckBox* checkBox = new QCheckBox;
        checkBox->setText(value);
        checkBox->setToolTip(value);
        listCheckBox.append(checkBox);
    }

    return listCheckBox;
}
