#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include <queue>
#include <QMutex>
#include <QThread>

class Payment;

class PaymentService : public QThread
{
    Q_OBJECT
private:
    std::priority_queue<Payment*> _paymentQueue;
    QMutex _mutex;
    //some DB connectors?
    void performPayment();
protected:
    void run();
public:
    PaymentService();
    ~PaymentService();
    void addPayment();
    unsigned int payment_amount() const;
};

#endif // PAYMENTSERVICE_H
