#ifndef USER_TABLE_H
#define USER_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/user.h"

class User;
class UserTable
{
public:
    UserTable(Connection&);
    ~UserTable();
    bool create_new(const User&);
    bool update(const User&);
    User get_by_upid(const quint64);
    User get_by_upid(const User& u) {return get_by_upid(u.upid());}
private:
    Connection& _connection;

    UserTable();
    bool delete_it(const uint);
};

#endif // USER_TABLE_H
