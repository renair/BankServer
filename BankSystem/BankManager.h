#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include<QThread>
#include "PaymentService.h"

class Payment;

class BankManager
{
private:
    PaymentService _paymentService;
    QThread _paymentThread;
public:
    BankManager();
    ~BankManager();
    void addPayment(Payment*);
    unsigned int paymentAmount() const;
};

#endif // BANKMANAGER_H
