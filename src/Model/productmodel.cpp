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
   QSqlQuery* query= select(request);

   if(query == nullptr)
       return;

   list.clear();
   while(query->next())
       list.append(query->value(0).toString());

   delete query;
}

