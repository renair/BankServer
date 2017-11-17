#ifndef USER_TABLE_H
#define USER_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/user.h"

class User;
class UserTable
{
public:
    UserTable();
    ~UserTable();
    bool createNew(const User&);
    bool update(const User&);
    User getByUpid(quint64);
private:
    Connection& _connection;

    UserTable& operator =(const UserTable&);
public:
    class UserTableError
    {
    public:
        UserTableError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;

        UserTableError();
    };
};

#endif // USER_TABLE_H
