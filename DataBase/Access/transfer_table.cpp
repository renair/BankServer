#include <QVariant>
#include "transfer_table.h"

TransferTable::TransferTable(Connection& c): _connection(c)
{}

TransferTable::~TransferTable()
{}

bool TransferTable::create_new(Transfer & t)
{
    /*TODO*/
    return true;
}

bool TransferTable::update(Transfer &t)
{
    /*TODO*/
    return true;
}

Transfer TransferTable::get_by_id(int id)
{
    try{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,payer,destination,time,technical_comment,comment,periodicity")+
                        " FROM payment"+
                        " WHERE id='"+QString::number(id)+"' AND is_withdraw='0'");
    q.next();
    Transfer t(q.value(0).toInt(),
               q.value(1).toInt(),
               q.value(2).toInt(),
               q.value(3).toInt(),
               q.value(4).toString(),
               q.value(5).toString());

    return t;
    }catch(const QString& error){
        throw error;
    }
}
