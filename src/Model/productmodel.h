#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include "basemodel.h"

#include <QSqlDatabase>

class ProductModel : public BaseModel
{
public:
    ProductModel(QSqlDatabase* db);

public:
    QList<QString> getListCategory(){ return listCategory; }
    QList<QString> getListCountry(){ return listCountry; }
    QList<QString> getListBrand(){ return listBrand; }
    void updateListFilter();
    void updateList(QList<QString>& list, QString request);
    void updateListForCharacteristic(QHash<QString, QString>& list, QString request);

private:
    QList<QString> listCategory;
    QList<QString> listCountry;
    QList<QString> listBrand;
};

#endif // PRODUCTMODEL_H
