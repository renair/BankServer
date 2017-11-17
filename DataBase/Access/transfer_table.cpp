#include <QVariant>
#include "transfer_table.h"

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
                        time,\
                        technical_comment,\
                        comment,\
                        periodicity,\
                        is_withdraw) \
                VALUES ('%1','%2','%3','%4','%5','%6',0)").
                arg(QString::number(t.payerId()),
                    QString::number(t.receiverId()),
                    QString::number(t.time()),
                    t.techComment(),
                    t.comment(),
                    QString::number(t.period()))).first;
}

Transfer TransferTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,time,technical_comment,comment,periodicity \
                         FROM payment \
                         WHERE id='%1' AND is_withdraw='0'").arg(QString::number(id))).second;
    if(!q.next())
            throw TransferTableError("Empty result");
    Transfer t(q.value(0).toULongLong(),
               q.value(1).toULongLong(),
               q.value(2).toULongLong(),
               q.value(3).toUInt(),
               q.value(4).toString(),
               q.value(5).toString());

    return t;
}

TransferTable::TransferTableError::TransferTableError(const QString & reason): _reason(reason)
{}
