#include <QList>
#include <QThread>
#include "PeriodicPaymentTask.h"

#include <iostream>
using namespace std;

PeriodicPaymentTask::PeriodicPaymentTask()
{}

PeriodicPaymentTask::~PeriodicPaymentTask()
{}

AbstractTaskHolder PeriodicPaymentTask::specificClone() const
{
    return AbstractTaskHolder(new PeriodicPaymentTask(*this));
}

void PeriodicPaymentTask::specificStartTaskLoop()
{
    while(isActive())
    {
        QList<Transfer> transfers = _transferTable.getPeriodicTransfersListToDo();
        if(transfers.length() > 0)
        {
            for(int i = 0; i < transfers.length();++i)
            {
                Transfer& t = transfers[i];
                //TODO paste make payment
            }
        }
        else
        {
            QThread::sleep(10);
        }
    }
}
