#include "menuemployeesviewmodel.h"

MenuEmployeesViewModel::MenuEmployeesViewModel(EmployeesModel* employeesModel) : BaseViewModel(),
    employeesModel(employeesModel)
{
    delegate = new DelegateForTableViewWorker(employeesModel->getListToRemove(), employeesModel->getModelData());
}

void MenuEmployeesViewModel::update()
{
    if(employeesModel->updateModel("worker"))
        emit modelChangedSignals(employeesModel->getModelData());
}

void MenuEmployeesViewModel::addToRemove(const int& row)
{
    employeesModel->addToRomove(row);
}

void MenuEmployeesViewModel::applyChanges()
{
    employeesModel->getModelData()->submitAll();

    //Удаление
    for (const int& id : employeesModel->getListToRemove())
        employeesModel->requestBD("call dropUser(" + QString::number(id) + ")");
}

MenuEmployeesViewModel::~MenuEmployeesViewModel()
{
    delete delegate;
}
