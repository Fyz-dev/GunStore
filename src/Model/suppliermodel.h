#ifndef SUPPLIERMODEL_H
#define SUPPLIERMODEL_H

#include "basemodel.h"

class SupplierModel : public BaseModel
{
public:
    SupplierModel(QSqlDatabase* db);
    void setHeaderModel() override;
    void addToRomove(const int& row);
    const QList<int>& getListToRemove() { return listToRemove; }

private:
    QList<int> listToRemove;
};

#endif // SUPPLIERMODEL_H
