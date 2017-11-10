#include "user.h"

User::User(const quint64 upid,
           const QString& password,
           const QString& pass_number,
           const QString& name,
           const QString& surname,
           const QString& father_name,
           const quint64 phone_number):
    _upid(upid),
    _password(password),
    _pass_number(pass_number),
    _name(name),
    _surname(surname),
    _father_name(father_name),
    _phone_number(phone_number)
{

}

bool User::checkPassword(const QString &password)
{
    return _password==password;
}

bool User::setNewPass(const QString &new_pass, const QString &old_pass)
{
    if(checkPassword(old_pass))
    {
        _password=new_pass;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const User& u)
{
    return os<< "User" <<endl<< "{" <<endl
             << " UPID: " << u.upid() <<endl
             << " Passport number: " << u.passNumber().toStdString() <<endl
             << " Name: " << u.name().toStdString() <<endl
             << " Surname: " << u.surname().toStdString() <<endl
             << " Father name: " << u.fatherName().toStdString() <<endl
             << " Phone number: " << u.phoneNumber() <<endl<< "}" <<endl;
}
