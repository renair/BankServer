#ifndef TRANSFER_TABLE_H
#define TRANSFER_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/transfer.h"

class TransferTable
{
public:
    TransferTable(Connection&);
    ~TransferTable();
    bool create_new(Transfer&);
    bool update(Transfer&);
    Transfer get_by_id(int);
private:
    Connection _connection;
};

#endif // TRANSFER_TABLE_H
