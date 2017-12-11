#include <QList>
#include <QThread>
#include <QDateTime>
#include "PeriodicPaymentTask.h"
#include "DataBase/Access/account_table.h"

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

void PeriodicPaymentTask::specificTask()
{
    QList<Transfer> transfers;
    try
    {
         transfers = _transferTable.getPeriodicTransfersListToDo();
    }
    catch(const Connection::ConnectionError& error)
    {
        cout<< "Problem: " << error.reason().toStdString() <<endl;
    }
    if(transfers.length() > 0)
    {
        AccountTable accountTable;
        for(int i = 0; i < transfers.length();++i)
        {
            try
            {
                quint64 time = QDateTime::currentDateTime().toTime_t();
                Transfer& t = transfers[i];
                Account payer = accountTable.getById(t.payerId());
                Account recipient = accountTable.getById(t.receiverId());
                payer.moneyDivide(t.amount());
                recipient.moneyAdd(t.amount());
                Transfer newTransfer = Transfer(payer.id(),
                                                recipient.id(),
                                                t.amount(),
                                                time,
                                                t.techComment(),
                                                t.comment(),
                                                t.period());
                _transferTable.setPaymentNonPeriodic(t.id());
                _transferTable.createNew(newTransfer);
                accountTable.update(payer);
                accountTable.update(recipient);
            }
            catch(...)
            {}
        }
    }
}
