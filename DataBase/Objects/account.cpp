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

/*Account::Account(const qint64 id,
                 const qint64 owner,
                 const int type,
                 const QString &pin,
                 const qint64 money)
{
    if(id<0)
        throw AccountError(QString("Card number ( %1 ) cannot have negative value.").
                           arg(QString::number(id)));
    if(owner<0)
        throw AccountError(QString("User UPID ( %1 ) cannot have negative value.")
                           .arg(QString::number(owner)));
    if(money<0)
        throw AccountError(QString("Money amount ( %1 ) cannot have negative value, please, use other type of card")
                           .arg(QString::number(money)));
    Account(id,owner,type,pin,money);
}*/

quint32 Account::money_add(qint32 value)
{
    if(value<0)
        throw AccountError(QString("Trying to add negative value ( %1 ), please, use money_divide(%2);")
                           .arg(QString::number(value),QString::number(value*(-1))));
    return _money_amount+=value;
}

quint32 Account::money_divide(qint32 value)
{
    if(value<0)
        throw AccountError(QString("Trying to divide negative value -(%1), please, use money_add(%2);")
                           .arg(QString::number(value),QString::number(value*(-1))));
    if(_money_amount < (quint32)value) //TODO fix it!
        throw AccountError("Not enough money.");
    return _money_amount-=value;
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

Account::AccountError::AccountError(const QString& reason): _reason(reason)
{}
