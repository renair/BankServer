#include <QVariant>
#include <QDebug>
#include "account_table.h"

AccountTable::AccountTable(): _connection(Connection::getConnection())
{}

AccountTable::~AccountTable()
{}

bool AccountTable::createNew(const Account & account)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM account \
                         WHERE ID='%1'").arg(account.id())).second;
    if(is_exist.next())
            throw AccountTableError("Unable to create an existing object");
    return _connection.execute(QString("INSERT INTO account(\
                                              ID,\
                                              type,\
                                              owner,\
                                              pin,\
                                              money_amount, \
                                              login_failed) \
                            VALUES (%1,%2,%3,'%4','%5','%6')").
                            arg(QString::number(account.id()),
                                QString::number(account.type()),
                                QString::number(account.owner()),
                                account.pin(),
                                QString::number(account.moneyAmount()),
                                QString::number(account.loginFailed()))).first;
}

bool AccountTable::update(const Account & account)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM account \
                         WHERE ID='%1'").arg(account.id())).second;
            if(!is_exist.next())
            throw AccountTableError("Unable to update non-existent object");
    return _connection.execute(
        QString("UPDATE account "
                "SET pin='%2',\
                     money_amount='%3', \
                     login_failed='%4', \
                     type='%5' \
                 WHERE ID='%1'").
                arg(QString::number(account.id()),
                    account.pin(),
                    QString::number(account.moneyAmount()),
                    QString::number(account.loginFailed()),
                    QString::number(account.type()))).first;
}

Account AccountTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,owner,type,pin,money_amount,login_failed\
                         FROM account \
                         WHERE ID='%1'").arg(QString::number(id))).second;
    if(!q.next())
            throw AccountTableError("The object does not exist");
    return Account(q.value(0).toULongLong(),
                   q.value(1).toULongLong(),
                   q.value(2).toInt(),
                   q.value(3).toString(),
                   q.value(4).toULongLong(),
                   q.value(5).toUInt());
}

QMap<quint64, qint8> AccountTable::getUserAccountsList(const quint64 user_upid)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,type\
                         FROM account \
                         WHERE owner='%1'").arg(QString::number(user_upid))).second;
    QMap<quint64, qint8> result;
    while(q.next())
    {
        result.insert(q.value(0).toULongLong(),q.value(1).toInt());
    }
    return result;
}

quint64 AccountTable::getOwnerById(const quint64 card_id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT owner\
                         FROM account \
                         WHERE ID='%1'").arg(QString::number(card_id))).second;
            if(!q.next()) {throw AccountTableError("Wrong card number");}
            return q.value(0).toULongLong();
}

bool AccountTable::blockAccount(Account & acc)
{
    if(acc.loginFailed()<3) return false;
    if(acc.type()>0) acc.type()*=(-1);
    return update(acc);
}

AccountTable::AccountTableError::AccountTableError(const QString & reason): _reason(reason)
{}
