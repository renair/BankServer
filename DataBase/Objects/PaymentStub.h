#ifndef PAYMENTSTUB_H
#define PAYMENTSTUB_H

#include "Payment.h"

class PaymentStub : public Payment
{
private:
    bool specificPerform();
    int _amount;
public:
    PaymentStub(int amount = 100);
    ~PaymentStub(){}
};

#endif // PAYMENTSTUB_H
