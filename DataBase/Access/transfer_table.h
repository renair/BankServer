#ifndef TRANSFER_TABLE_H
#define TRANSFER_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/transfer.h"

class TransferTable
{
public:
    TransferTable(Connection&);
    ~TransferTable();
    bool create_new(const Transfer&);
    Transfer getById(const quint64);
private:
    Connection& _connection;

    TransferTable();
};

#endif // TRANSFER_TABLE_H
