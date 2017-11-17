#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include <queue>
#include <QObject>
#include <QMutex>
#include "../DataBase/Objects/transfer.h"

class PaymentService : public QObject
{
    Q_OBJECT
private:
//    std::priority_queue<Payment*> _paymentQueue;
    QMutex _mutex;
    //some DB connectors?
private slots:
    void savePendingPayments();
    void loadPendingPayments();
public:
    PaymentService();
    ~PaymentService();
//    void addPayment(Payment*);
    unsigned int paymentsAmount() const;
public slots:
    void startService();
};

#endif // PAYMENTSERVICE_H
