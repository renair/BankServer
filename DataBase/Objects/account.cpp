#include "account.h"
#include "DataBase/Access/account_table.h"

Account::Account(quint64 id,
                 quint64 owner,
                 int type,
                 const QString& pin,
                 quint32 money,
                 uint login_failed):
    _id(id),
    _owner(owner),
    _type(type),
    _pin(pin),
    _money_amount(money),
    _login_failed(login_failed)
{}

quint32 Account::moneyAdd(qint32 value)
{
    if(blocked())
        throw AccountError("Card is blocked.");
    if(value<0)
        throw AccountError(QString("Trying to add negative value ( %1 ), please, use money_divide(%2);")
                           .arg(QString::number(value),QString::number(value*(-1))));
    return _money_amount+=value;
}

quint32 Account::moneyDivide(qint32 value)
{
    if(blocked())
        throw AccountError("Card is blocked.");
    if(value<0)
        throw AccountError(QString("Trying to divide negative value -(%1), please, use money_add(%2);")
                           .arg(QString::number(value),QString::number(value*(-1))));
    if(_money_amount < (quint32)value)
        throw AccountError("Not enough money.");
    return _money_amount-=(quint32)value;
}

bool Account::checkPin(const QString & s)
{
    if(s!=_pin || blocked())
    {
        if(blocked() || ++_login_failed>=3)
        {
            type()*=(type()>0?(-1):1);
            _login_failed=0;
        }
        try
        {
            AccountTable().update(*this);
        }
        catch(...)
        {}
        return false;
    }
    else
    {
        AccountTable().resetFailedLogins(id());
        return true;
    }
}

bool Account::setNewPin(const QString& new_pin, const QString& old_pin)
{
    if(checkPin(old_pin) && !blocked())
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
