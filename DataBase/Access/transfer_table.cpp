#include <QVariant>
#include <QDateTime>
#include "transfer_table.h"

#include <iostream>
using namespace std;

TransferTable::TransferTable(): _connection(Connection::getConnection())
{}

TransferTable::~TransferTable()
{}

bool TransferTable::createNew(const Transfer &t)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM payment \
                         WHERE ID='%1' AND is_withdraw='0'").arg(t.id())).second;
    if(is_exist.next())
            throw TransferTableError("Unable to create an existing object");
    return _connection.execute(
                QString("INSERT INTO payment(\
                        payer,\
                        destination,\
                        amount,\
                        time,\
                        technical_comment,\
                        comment,\
                        periodicity,\
                        is_withdraw) \
                VALUES ('%1','%2','%3','%4','%5','%6','%7',0)").
                arg(QString::number(t.payerId()),
                    QString::number(t.receiverId()),
                    QString::number(t.amount()),
                    QString::number(t.time()),
                    t.techComment(),
                    t.comment(),
                    QString::number(t.period()))).first;
}

Transfer TransferTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,amount,time,technical_comment,comment,periodicity \
                         FROM payment \
                         WHERE id='%1' AND is_withdraw='0'").arg(QString::number(id))).second;
    if(!q.next())
            throw TransferTableError("Empty result");
    return Transfer(q.value(0).toULongLong(),
                    q.value(1).toULongLong(),
                    q.value(2).toULongLong(),
                    q.value(3).toULongLong(),
                    q.value(4).toUInt(),
                    q.value(5).toString(),
                    q.value(6).toString());
}

QList<Transfer> TransferTable::getTransfersFromAccount(const quint64 id)
{
    QList<Transfer> list;
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,amount,time,technical_comment,comment,periodicity \
                         FROM payment \
                         WHERE payer='%1' AND is_withdraw='0'").arg(QString::number(id))).second;         
    while(q.next())
    {
        list.append(
           Transfer(q.value(0).toULongLong(),
                    q.value(1).toULongLong(),
                    q.value(2).toULongLong(),
                    q.value(3).toULongLong(),
                    q.value(4).toUInt(),
                    q.value(5).toString(),
                    q.value(6).toString()));
    }
    return list;
}

QList<Transfer> TransferTable::getPeriodicTransfersFromAccount(const quint64 id)
{
    QList<Transfer> list;
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,amount,time,technical_comment,comment,periodicity \
                         FROM payment \
                         WHERE payer='%1' AND is_withdraw='0' AND periodicity>0").arg(QString::number(id))).second;
    while(q.next())
    {
        list.append(
           Transfer(q.value(0).toULongLong(),
                    q.value(1).toULongLong(),
                    q.value(2).toULongLong(),
                    q.value(3).toULongLong(),
                    q.value(4).toUInt(),
                    q.value(5).toString(),
                    q.value(6).toString()));
    }
    return list;
}

bool TransferTable::setPaymentNonPeriodic(const quint64 id)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM payment \
                         WHERE ID='%1' AND is_withdraw='0'").arg(id)).second;
            if(!is_exist.next())
            throw TransferTableError("Unable to update non-existent object");
    return _connection.execute(
        QString("UPDATE payment \
                 SET periodicity=0 \
                 WHERE ID='%1'").
                arg(QString::number(id))).first;
}

bool TransferTable::setPaymentNonPeriodic(Transfer &t)
{
    t.period()=0;
    return setPaymentNonPeriodic(t.id());
}

QList<Transfer> TransferTable::getPeriodicTransfersListToDo()
{
    QList<Transfer> list;
    quint64 time = QDateTime::currentDateTime().toTime_t();
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,amount,time,technical_comment,comment,periodicity \
                         FROM payment \
                         WHERE periodicity > 0 AND time+periodicity < %1").arg(QString::number(time))).second;
    while(q.next())
    {
        list.append(
           Transfer(q.value(0).toULongLong(),
                    q.value(1).toULongLong(),
                    q.value(2).toULongLong(),
                    q.value(3).toULongLong(),
                    q.value(4).toULongLong(),
                    q.value(5).toString(),
                    q.value(6).toString(),
                    q.value(7).toULongLong()));
    }
    return list;
}

TransferTable::TransferTableError::TransferTableError(const QString & reason): _reason(reason)
{}
