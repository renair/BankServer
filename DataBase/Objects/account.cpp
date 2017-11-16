#include "account.h"

Account::Account(quint64 id,
                 quint64 owner,
                 int type,
                 const QString& pin,
                 quint32 money):
    _id(id),
    _owner(owner),
    _type(type),
    _pin(pin),
    _money_amount(money)
{

}

quint32 Account::moneyAdd(qint32 value)
{
    if(value<0)
        throw AccountError(QString("Trying to add negative value ( %1 ), please, use money_divide(%2);")
                           .arg(QString::number(value),QString::number(value*(-1))));
    return _money_amount+=value;
}

quint32 Account::moneyDivide(qint32 value)
{
    if(value<0)
        throw AccountError(QString("Trying to divide negative value -(%1), please, use money_add(%2);")
                           .arg(QString::number(value),QString::number(value*(-1))));
    if(_money_amount < (quint32)value) //TODO fix it!
        throw AccountError("Not enough money.");
    return _money_amount-=(quint32)value;
}

bool Account::checkPin(const QString& pin)
{
    return _pin==pin;
}

bool Account::setNewPin(const QString& new_pin, const QString& old_pin)
{
    if(checkPin(old_pin))
    {
        _pin=new_pin;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Account& a)
{
    return os<< "Account" <<endl<< "{" <<endl
             << " ID: " << a.id() <<endl
             << " Owner: " << a.owner() <<endl
             << " Type: " << a.type() <<endl
             << " Money amount: " << a.moneyAmount() <<endl<< "}" <<endl;
}

Account::AccountError::AccountError(const QString& reason): _reason(reason)
{}
