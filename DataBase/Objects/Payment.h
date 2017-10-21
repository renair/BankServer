#ifndef PAYMENT_H
#define PAYMENT_H

class Payment
{
private:
    virtual bool specificPerform() = 0;
public:
    //NonVirtualInterface
    bool perform();
    virtual ~Payment(){}
};

#endif // PAYMENT_H
