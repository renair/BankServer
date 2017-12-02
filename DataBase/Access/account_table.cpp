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
                                              money_amount) \
                            VALUES (%1,%2,%3,'%4',%5)").
                            arg(QString::number(account.id()),
                                QString::number(account.type()),
                                QString::number(account.owner()),
                                account.pin(),
                                QString::number(account.moneyAmount()))).first;
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
                     money_amount='%3' \
                 WHERE ID='%1'").
                arg(QString::number(account.id()),
                    account.pin(),
                    QString::number(account.moneyAmount()))).first;
}

Account AccountTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,owner,type,pin,money_amount\
                         FROM account \
                         WHERE ID='%1'").arg(QString::number(id))).second;
    if(!q.next())
            throw AccountTableError("The object does not exist");
    return Account(q.value(0).toULongLong(),
                   q.value(1).toULongLong(),
                   q.value(2).toInt(),
                   q.value(3).toString(),
                   q.value(4).toULongLong());

//    return a;
}

QMap<quint64, quint8> AccountTable::getUserAccountsList(const quint64 user_upid)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,type\
                         FROM account \
                         WHERE owner='%1'").arg(QString::number(user_upid))).second;
    QMap<quint64, quint8> result;
    while(q.next())
    {
        result.insert(q.value(0).toULongLong(),q.value(1).toUInt());
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

AccountTable::AccountTableError::AccountTableError(const QString & reason): _reason(reason)
{}
