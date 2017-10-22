#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

#include<QThread>
#include "PaymentService.h"

class Payment;

class PaymentManager
{
private:
    PaymentService _paymentService;
    QThread _paymentThread;
public:
    PaymentManager();
    ~PaymentManager();
    void addPayment(Payment*);
    unsigned int paymentAmount() const;
};

#endif // PAYMENTMANAGER_H
