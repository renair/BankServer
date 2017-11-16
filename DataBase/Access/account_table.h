#ifndef ACCOUNT_TABLE_H
#define ACCOUNT_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/account.h"

class AccountTable
{
public:
    AccountTable();
    ~AccountTable();
    bool createNew(const Account&);
    bool update(const Account&);
    Account getById(const quint64);
private:
    Connection& _connection;

    AccountTable& operator=(const AccountTable&);

public:
    class AccountTableError
    {
    public:
        AccountTableError(const QString&);
        const QString& reason() {return _reason;}
    private:
        QString _reason;

        AccountTableError();
    };
};

#endif // ACCOUNT_TABLE_H
