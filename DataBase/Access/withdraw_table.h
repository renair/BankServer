#ifndef WITHDRAW_TABLE_H
#define WITHDRAW_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/withdraw.h"

class WithdrawTable
{
public:
    WithdrawTable();
    ~WithdrawTable();
    bool createNew(const Withdraw&);
    Withdraw getById(const quint64);
private:
    Connection& _connection;

    WithdrawTable& operator=(const WithdrawTable&);
public:
    class WithdrawTableError
    {
    public:
        WithdrawTableError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;

        WithdrawTableError();
    };
};

#endif // WITHDRAW_TABLE_H
