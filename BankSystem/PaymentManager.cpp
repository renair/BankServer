#include "PaymentManager.h"
#include <QObject>

PaymentManager::PaymentManager()
{
    _paymentService.moveToThread(&_paymentThread);
    QObject::connect(&_paymentThread, SIGNAL(started()), &_paymentService, SLOT(loadPendingPayments()));
    QObject::connect(&_paymentThread, SIGNAL(finished()), &_paymentService, SLOT(savePendingPayments()));
    _paymentThread.start(QThread::HighestPriority);
}

PaymentManager::~PaymentManager()
{
    _paymentThread.quit();
    _paymentThread.wait();
}

void PaymentManager::addPayment(Payment* newOperation)
{
    qDebug("Payment manager add Payment");
    _paymentService.addPayment(newOperation);
}

unsigned int PaymentManager::paymentAmount() const
{
    return _paymentService.paymentsAmount();
}
