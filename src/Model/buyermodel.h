#ifndef BUYERMODEL_H
#define BUYERMODEL_H

#include "basemodel.h"
#include "elementpeople.h"

class BuyerModel : public BaseModel
{
public:
    BuyerModel(ConnectionHandler* connectionHandler);
    QList<ElementPeople*>& updateInfoBuyPeople(QWidget* parent);

private:
    void setHeaderModel() override;

private:
    QList<ElementPeople*> list;
};

#endif // BUYERMODEL_H
