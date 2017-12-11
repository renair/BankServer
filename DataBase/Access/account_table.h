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
    bool blockAccount(Account&);
    bool resetFailedLogins(const quint64);
    Account getById(const quint64 account_id);
    QMap<quint64, qint8> getUserAccountsList(const quint64 user_upid);
    quint64 getOwnerById(const quint64);
private:
    Connection& _connection;

    AccountTable& operator=(const AccountTable&);

public:
    class AccountTableError
    {
    public:
        AccountTableError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;

        AccountTableError();
    };
};

#endif // ACCOUNT_TABLE_H
