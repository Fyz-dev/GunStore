#ifndef SUPPLIERMODEL_H
#define SUPPLIERMODEL_H

#include "basemodel.h"
#include "elementpeople.h"

class SupplierModel : public BaseModel
{
public:
    SupplierModel(ConnectionHandler* connection);
    void setHeaderModel() override;
    QList<ElementPeople*>& updateInfoBuyPeople(QWidget* parent);
private:
    QList<ElementPeople*> list;
};

#endif // SUPPLIERMODEL_H
