#include <QVariant>
#include "withdraw_table.h"

WithdrawTable::WithdrawTable(Connection& c): _connection(c)
{}

WithdrawTable::~WithdrawTable()
{}

bool WithdrawTable::create_new(const Withdraw &w)
{
    return _connection.execute(
                QString("INSERT INTO payment(\
                        payer,\
                        destination,\
                        time,\
                        technical_comment,\
                        comment,\
                        is_withdraw) \
                VALUES ('%1','%2','%3','%4','%5',1)").
                arg(QString::number(w.payerId()),
                    QString::number(w.atmId()),
                    QString::number(w.time()),
                    w.techComment(),
                    w.comment())).first;
}

Withdraw WithdrawTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,time,technical_comment,comment \
                         FROM payment \
                         WHERE id='%1' AND is_withdraw='1'").arg(QString::number(id))).second;
    if(!q.next())
            throw QString("Empty result");
    return Withdraw(q.value(0).toInt(),
                    q.value(1).toInt(),
                    q.value(2).toInt(),
                    q.value(3).toInt(),
                    q.value(4).toString(),
                    q.value(5).toString());

//    return w;
}
