#include "PaymentService.h"

PaymentService::PaymentService()
{
    qDebug("Payment Service inited!");
}

PaymentService::~PaymentService()
{
    qDebug("Payment Service deleted!");
}

void PaymentService::startService()
{
    qDebug("Payment Service started!");
}

void PaymentService::savePendingPayments()
{
    qDebug("Payment Service save pending tasks!");
}

void PaymentService::loadPendingPayments()
{
    qDebug("Payment Service load pending tasks!");
}

void PaymentService::addPayment(Payment* newOperation)
{
    //TODO fix it bacouse for ptrs defined comparison operation
    _paymentQueue.push(newOperation);
}

unsigned int PaymentService::paymentsAmount() const
{
    return _paymentQueue.size();
}
