#include <QList>
#include <QThread>
#include "PeriodicPaymentTask.h"

#include <iostream>
using namespace std;

PeriodicPaymentTask::PeriodicPaymentTask()
{
    qDebug("Periodic payment service initialized");
}

PeriodicPaymentTask::~PeriodicPaymentTask()
{
    qDebug("Periodic payment service deinitialized");
}

AbstractTaskHolder PeriodicPaymentTask::specificClone() const
{
    return AbstractTaskHolder(new PeriodicPaymentTask(*this));
}

void PeriodicPaymentTask::specificStartTaskLoop()
{
    while(isActive())
    {
        //TODO implement and remove redundant code
        QList<Transfer> transfers = _transferTable.getPeriodicTransfersListToDo();
        if(transfers.length() > 0)
        {
            for(int i = 0; i < transfers.length();++i)
            {
                Transfer& t = transfers[i];
                cout << t.id() << ' ' << t.amount() << endl;
            }
            cout << endl;
            cout.flush();
            QThread::sleep(1);
        }
        else
        {
            QThread::sleep(1); //TODO set to 10
        }
    }
}
