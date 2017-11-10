#include <QVariant>
#include "transfer_table.h"

TransferTable::TransferTable(Connection& c): _connection(c)
{}

TransferTable::~TransferTable()
{}

bool TransferTable::create_new(const Transfer &t)
{
    return _connection.execute(
                QString("INSERT INTO payment(\
                        payer,\
                        destination,\
                        time,\
                        technical_comment,\
                        comment,\
                        periodicity) \
                VALUES ('%1','%2','%3','%4','%5','%6')").
                arg(QString::number(t.payerId()),
                    QString::number(t.receiverId()),
                    QString::number(t.time()),
                    t.techComment(),
                    t.comment(),
                    QString::number(t.period()))).first;
}

Transfer TransferTable::get_by_id(const int id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,time,technical_comment,comment,periodicity \
                         FROM payment \
                         WHERE id='%1' AND is_withdraw='0'").arg(QString::number(id))).second;
    if(!q.next())
            throw QString("Empty result");
    Transfer t(q.value(0).toInt(),
               q.value(1).toInt(),
               q.value(2).toInt(),
               q.value(3).toInt(),
               q.value(4).toString(),
               q.value(5).toString());

    return t;
}
