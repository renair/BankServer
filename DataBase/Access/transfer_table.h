#ifndef TRANSFER_TABLE_H
#define TRANSFER_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/transfer.h"

class TransferTable
{
public:
    TransferTable();
    ~TransferTable();
    bool createNew(const Transfer&);
    Transfer getById(const quint64);
    QList<Transfer> getTransfersFromAccount(const quint64);
    QList<Transfer> getPeriodicTransfersFromAccount(const quint64);
    bool setPaymentNonPeriodic(const quint64 id);
    bool setPaymentNonPeriodic(Transfer&);
    QList<Transfer> getPeriodicTransfersListToDo();
private:
    Connection& _connection;

    TransferTable& operator=(const TransferTable&);
public:
    class TransferTableError
    {
    public:
        TransferTableError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;

        TransferTableError();
    };
};

#endif // TRANSFER_TABLE_H
