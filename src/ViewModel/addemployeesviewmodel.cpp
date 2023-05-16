#include "addemployeesviewmodel.h"

AddEmployeesViewModel::AddEmployeesViewModel(EmployeesModel* employeesModel) : BaseViewModel(),
    employeesModel(employeesModel)
{}

void AddEmployeesViewModel::update()
{
    emit addItemsToComboBox({"Чоловік", "Жінка"}, {"Адміністратор", "Продавець"});
}

void AddEmployeesViewModel::applyChanges(const QString& FIO, const QString& password, const QString& position, const QString& phoneNumber, const QString& address, const QString& gender, const QString& date)
{
    if(employeesModel->requestBD("INSERT INTO worker(w_full_name, position, w_phoneNum, w_address, gender, birthday) VALUES('"+ FIO + "','" +
                              position + "','" + phoneNumber + "','" + address + "','" + gender + "','" + date +"')"))
    {
        if(position == "Продавець")
            employeesModel->requestBD("call createCasir('" + FIO + "','" + password + "')");
        else
            employeesModel->requestBD("call createAdmin('" + FIO + "','" + password + "')");
        emit close();
        return;
    }
}

bool AddEmployeesViewModel::isEmployees(const QString& text)
{
    if(employeesModel->getOneCell(QString("select count(*) from worker where w_full_name = '%1'").arg(text)) == "0")
        return false;

    return true;
}

AddEmployeesViewModel::~AddEmployeesViewModel()
{
    delete employeesModel;
}
