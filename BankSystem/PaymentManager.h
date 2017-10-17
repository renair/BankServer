#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

#include "PaymentService.h"

class Payment;

class PaymentManager
{
private:
    PaymentService _paymentService;
public:
    PaymentManager();
    ~PaymentManager();
    void addPayment(Payment*);
    unsigned int payment_amount() const;
};

#endif // PAYMENTMANAGER_H
