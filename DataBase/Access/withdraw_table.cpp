#include <QVariant>
#include "withdraw_table.h"

WithdrawTable::WithdrawTable(): _connection(Connection::getConnection())
{}

WithdrawTable::~WithdrawTable()
{}

bool WithdrawTable::createNew(const Withdraw &w)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM payment \
                         WHERE ID='%1' AND is_withdraw='1'").arg(w.id())).second;
    if(is_exist.next())
            throw WithdrawTableError("Unable to create an existing object");
    return _connection.execute(
                QString("INSERT INTO payment(\
                        payer,\
                        destination,\
                        amount,\
                        time,\
                        technical_comment,\
                        comment,\
                        is_withdraw) \
                VALUES ('%1','%2','%3','%4','%5','%6',1)").
                arg(QString::number(w.payerId()),
                    QString::number(w.atmId()),
                    QString::number(w.amount()),
                    QString::number(w.time()),
                    w.techComment(),
                    w.comment())).first;
}

Withdraw WithdrawTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,amount,time,technical_comment,comment \
                         FROM payment \
                         WHERE id='%1' AND is_withdraw='1'").arg(QString::number(id))).second;
    if(!q.next())
            throw WithdrawTableError("Empty result");
    return Withdraw(q.value(0).toULongLong(),
                    q.value(1).toULongLong(),
                    q.value(2).toULongLong(),
                    q.value(3).toULongLong(),
                    q.value(4).toULongLong(),
                    q.value(5).toString(),
                    q.value(6).toString());

//    return w;
}

WithdrawTable::WithdrawTableError::WithdrawTableError(const QString & reason): _reason(reason)
{}
