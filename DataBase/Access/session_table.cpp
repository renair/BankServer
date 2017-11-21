#include <QVariant>
#include <QDebug>
#include <QDateTime>
#include "session_table.h"

SessionTable::SessionTable(): _connection(Connection::getConnection())
{}

SessionTable::~SessionTable()
{}

bool SessionTable::createNew(Session& s)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT signature \
                         FROM session \
                         WHERE signature='%1'").arg(s.signature())).second;
            if(is_exist.next())
            throw SessionTableError("Unable to create an existing object");
    std::pair<bool, QSqlQuery> result =
            _connection.execute(QString("INSERT INTO session(\
                                                   signature,\
                                                   auth_time,\
                                                   user_upid,\
                                                   valid) \
                                        VALUES (null,'%1','%2','%3')"). //null bacause of auto increment!!!
                                        arg(QString::number(s.authTime()),
                                            QString::number(s.userUpid()),
                                            QString::number(s.validTime())));
    s.signature() = result.second.lastInsertId().toInt();
    return result.first;
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

Session SessionTable::getBySignature(const quint64 signature)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT signature,auth_time,user_upid,valid \
                         FROM session \
                         WHERE signature='%1'").arg(QString::number(signature))).second;
    if(!q.next())
            throw SessionTableError("It seems you want to hack me)");
    return Session(q.value(0).toULongLong(),
              q.value(1).toULongLong(),
              q.value(2).toULongLong(),
              q.value(3).toULongLong());

//    return s;
}

bool SessionTable::renewSession(const quint64 signature)
{
    try
    {
        quint64 time = QDateTime::currentDateTime().toTime_t();
        Session session = getBySignature(signature);
        if(session.validTime()<time)
            return false;
        session.renewValidTime(time+1800);
        return update(session);
    }
    catch(const SessionTable::SessionTableError&)
    {
        return false;
    }
    catch(const Session::SessionError&)
    {
        return false;
    }
}

pair<bool,quint64> SessionTable::isAuthorized(const quint64 user_upid)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT signature,auth_time,user_upid,valid \
                         FROM session \
                         WHERE user_upid='%1' AND valid>'%2'").
            arg(QString::number(user_upid),QString::number(QDateTime::currentDateTime().toTime_t()))).second;
    if(q.next())
    {
        return make_pair(true,q.value(0).toULongLong());
    }
    else
    {
        return make_pair(false,0);
    }

}

quint64 SessionTable::getUserBySignature(const quint64 session_signature)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT user_upid \
                         FROM session \
                         WHERE signature='%1'").arg(session_signature)).second;
    if(q.next())
            return q.value(0).toULongLong();
    throw SessionTableError("Session does not exist");
}

SessionTable::SessionTableError::SessionTableError(const QString & reason): _reason(reason)
{}
