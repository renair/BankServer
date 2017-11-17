#ifndef SESSION_TABLE_H
#define SESSION_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/session.h"

class SessionTable
{
public:
    SessionTable();
    ~SessionTable();
    bool createNew(const Session&);
    bool update(const Session&);
    Session getBySignature(quint64);
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
