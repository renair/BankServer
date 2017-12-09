#ifndef SESSION_TABLE_H
#define SESSION_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/session.h"

class SessionTable
{
public:
    SessionTable();
    ~SessionTable();
    bool createNew(Session&);
    bool update(const Session&);
    Session getBySignature(const quint64);
    quint64 getUserBySignature(const quint64);
    bool renewSession(const quint64);
    pair<bool,quint64> isAuthorized(const quint64 user_upid, const quint64 card_id);
private:
    Connection& _connection;

    SessionTable& operator =(const SessionTable&);
public:
    class SessionTableError
    {
    public:
        SessionTableError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;

        SessionTableError();
    };
};

#endif // SESSION_TABLE_H
