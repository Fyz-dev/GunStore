#include "menusupplierviewmodel.h"

MenuSupplierViewModel::MenuSupplierViewModel(SupplierModel* supplierModel) : BaseViewModel(),
    supplierModel(supplierModel)
{
    delegate = new DelegateForTableView(supplierModel->getListToRemove(), supplierModel->getModelData());
}

void MenuSupplierViewModel::update()
{
    if(supplierModel->updateModel("supplier"))
        emit modelChangedSignals(supplierModel->getModelData());
}

void MenuSupplierViewModel::applyChanges()
{
    supplierModel->getModelData()->submitAll();
    for (const int& id : supplierModel->getListToRemove())
        supplierModel->requestBD("DELETE FROM supplier where id_supplier = " + QString::number(id));
}

void MenuSupplierViewModel::addToRemove(const int& row)
{
    supplierModel->addToRomove(row);
}

MenuSupplierViewModel::~MenuSupplierViewModel()
{
    delete delegate;
}
