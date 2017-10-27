#ifndef PAYMENT_H
#define PAYMENT_H

#include <QString>

class Payment
{
public:
    //NonVirtualInterface
    bool perform();
    virtual ~Payment(){}
private:
    virtual bool specificPerform() = 0;
};

#endif // PAYMENT_H
