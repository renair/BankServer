#include <QVariant>
#include <QDebug>
#include "session_table.h"

SessionTable::SessionTable(): _connection(Connection::getConnection())
{}

SessionTable::~SessionTable()
{}

bool SessionTable::createNew(const Session & s)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT signature \
                         FROM session \
                         WHERE signature='%1'").arg(s.signature())).second;
            if(is_exist.next())
            throw SessionTableError("Unable to create an existing object");
    return _connection.execute(QString("INSERT INTO session(\
                                       signature,\
                                       auth_time,\
                                       user_upid,\
                                       valid) \
                            VALUES ('%1','%2','%3','%4')").
                            arg(QString::number(s.signature()),
                                QString::number(s.authTime()),
                                QString::number(s.userUpid()),
                                QString::number(s.validTime()))).first;
}

bool SessionTable::update(const Session& s)
{QSqlQuery is_exist = _connection.execute(
                QString("SELECT signature \
                         FROM session \
                         WHERE signature='%1'").arg(s.signature())).second;
            if(!is_exist.next())
            throw SessionTableError("Unable to update non-existent object");
    return _connection.execute(
        QString("UPDATE session "
                "SET valid='%2',\
                 WHERE UPID='%1'").
                arg(QString::number(s.signature()),
                    QString::number(s.validTime()))).first;
}

Session SessionTable::getBySignature(quint64 signature)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT signature,auth_time,user_upid,valid \
                         FROM session \
                         WHERE signature='%1'").arg(QString::number(signature))).second;
    if(!q.next())
            throw SessionTableError("The object does not exist");
    Session s(q.value(0).toULongLong(),
              q.value(1).toULongLong(),
              q.value(2).toULongLong(),
              q.value(3).toULongLong());

    return s;
}

SessionTable::SessionTableError::SessionTableError(const QString & reason): _reason(reason)
{}
