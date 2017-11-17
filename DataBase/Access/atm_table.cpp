#include <QVariant>
#include <QDebug>
#include "atm_table.h"

ATMTable::ATMTable(): _connection(Connection::getConnection())
{}

ATMTable::~ATMTable()
{}

bool ATMTable::createNew(const ATM & atm)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM atm \
                         WHERE ID='%1'").arg(atm.id())).second;
            if(is_exist.next())
            throw ATMTableError("Unable to create an existing object");
    return _connection.execute(QString("INSERT INTO atm(\
                                               ID,\
                                               address,\
                                               available_10_uhr,\
                                               available_20_uhr,\
                                               available_50_uhr,\
                                               available_100_uhr,\
                                               available_200_uhr,\
                                               available_500_uhr) \
                            VALUES ('%1','%2','%3','%4','%5','%6','%7','%8')").
                            arg(QString::number(atm.id()),
                                atm.address(),
                                QString::number(atm.uhr_10()),
                                QString::number(atm.uhr_20()),
                                QString::number(atm.uhr_50()),
                                QString::number(atm.uhr_100()),
                                QString::number(atm.uhr_200()),
                                QString::number(atm.uhr_500()))).first;
}

bool ATMTable::update(const ATM & atm)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT ID \
                         FROM atm \
                         WHERE ID='%1'").arg(atm.id())).second;
            if(!is_exist.next())
            throw ATMTableError("Unable to update non-existent object");
    return _connection.execute(
        QString("UPDATE atm "
                "SET address='%2',\
                     available_10_uhr='%3',\
                     available_20_uhr='%4',\
                     available_50_uhr='%5',\
                     available_100_uhr='%6',\
                     available_200_uhr='%7',\
                     available_500_uhr='%8' \
                 WHERE ID='%1'").
                arg(QString::number(atm.id()),
                    atm.address(),
                    QString::number(atm.uhr_10()),
                    QString::number(atm.uhr_20()),
                    QString::number(atm.uhr_50()),
                    QString::number(atm.uhr_100()),
                    QString::number(atm.uhr_200()),
                    QString::number(atm.uhr_500()))).first;
}

ATM ATMTable::getById(const quint64 id)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT ID,\
                                address,\
                                available_10_uhr,\
                                available_20_uhr,\
                                available_50_uhr,\
                                available_100_uhr,\
                                available_200_uhr,\
                                available_500_uhr\
                         FROM atm \
                         WHERE ID='%1'").arg(QString::number(id))).second;
    if(!q.next())
            throw ATMTableError("The object does not exist");
    ATM a(q.value(0).toULongLong(),
          q.value(1).toString(),
          q.value(2).toUInt(),
          q.value(3).toUInt(),
          q.value(4).toUInt(),
          q.value(5).toUInt(),
          q.value(6).toUInt(),
          q.value(7).toUInt());

    return a;
}

ATMTable::ATMTableError::ATMTableError(const QString & reason): _reason(reason)
{}
