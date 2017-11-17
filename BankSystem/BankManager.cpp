#include "BankManager.h"
#include <QObject>

BankManager::BankManager()
{
    _paymentService.moveToThread(&_paymentThread);
    QObject::connect(&_paymentThread, SIGNAL(started()), &_paymentService, SLOT(loadPendingPayments()));
    QObject::connect(&_paymentThread, SIGNAL(finished()), &_paymentService, SLOT(savePendingPayments()));
    _paymentThread.start(QThread::HighestPriority);
}

BankManager::~BankManager()
{
    _paymentThread.quit();
    _paymentThread.wait();
}

//void BankManager::addPayment(Payment* newOperation)
//{
//    qDebug("Payment manager add Payment");
//    _paymentService.addPayment(newOperation);
//}

//unsigned int BankManager::paymentAmount() const
//{
//    return _paymentService.paymentsAmount();
//}
