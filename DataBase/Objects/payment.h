#ifndef PAYMENT_H
#define PAYMENT_H

#include <QString>

class Payment
{
public:
    //NonVirtualInterface
    bool perform()
    {
        return specificPerform();
    }

    bool isPeriodic()
    {
        return specificIsPeriodic();
    }

    Payment* nextPayment()
    {
        return specificNextPayment();
    }
    virtual ~Payment(){}
private:
    virtual bool specificPerform() = 0;
    virtual bool specificIsPeriodic()
    {
        return false;
    }

    virtual Payment* specificNextPayment()
    {
        return NULL;
    }
};

#endif // PAYMENT_H
