#ifndef PERIODICPAYMENTTASK_H
#define PERIODICPAYMENTTASK_H

#include "../AbstractTask.h"
#include "../../DataBase/Access/transfer_table.h"

class PeriodicPaymentTask : public AbstractTask
{
private:
    //variables
    TransferTable _transferTable;
    //methods
    virtual void specificTask();
    virtual AbstractTaskHolder specificClone() const;
    PeriodicPaymentTask& operator=(const PeriodicPaymentTask&) = delete;
public:
    PeriodicPaymentTask();
    PeriodicPaymentTask(const PeriodicPaymentTask& that):
        AbstractTask(that)
    {} //to create new TransferTable instead of copying it
    ~PeriodicPaymentTask();
};

#endif // PERIODICPAYMENTTASK_H
