#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include "basemodel.h"
#include "elementcharacteristic.h"
#include "elementbuyproduct.h"

#include <QSqlDatabase>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

class ProductModel : public QObject, public BaseModel
{
    Q_OBJECT

public:
    ProductModel(ConnectionHandler* connection);

public:
    //GET
    QList<QString> getListCategory(){ return listCategory; }
    QList<QString> getListCountry(){ return listCountry; }
    QList<QString> getListBrand(){ return listBrand; }
    QHash<int, QString>& getListChangedCharacteristic() { return listChangedCharacteristic; }
    const QString& getIdWorker() { return connection->getIdWorker(); }

    void buyProduct(const QString& nameSupplier, QList<ElementBuyProduct*>& listElement);
    void updateListFilter(const QString& isDelete = "0");
    void updateList(QList<QString>& list, QString request);
    void createElementForDispleyCharact(QString request, bool lineEditIsReadOnly = true);
    QList<QCheckBox*> createCheckBox(const QList<QString>& list);

public slots:
    void changedValueCharacteristicSlots(const ElementCharacteristic* element);

signals:
    void addInfoProductSignal(QWidget* widget);

private:
    void setHeaderModel() override;

private:
    QHash<int, QString> listChangedCharacteristic;
    QList<QString> listCategory;
    QList<QString> listCountry;
    QList<QString> listBrand;
};

#endif // PRODUCTMODEL_H
