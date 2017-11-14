#ifndef WITHDRAW_TABLE_H
#define WITHDRAW_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/withdraw.h"

class WithdrawTable
{
public:
    WithdrawTable(Connection&);
    ~WithdrawTable();
    bool create_new(const Withdraw&);
    Withdraw getById(const quint64);
private:
    Connection& _connection;

    WithdrawTable();
};

#endif // WITHDRAW_TABLE_H
