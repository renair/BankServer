#include "PaymentStub.h"
#include <QtCore>

PaymentStub::PaymentStub(int money):
    _amount(money)
{
    qDebug("New money widthraw");
}

bool PaymentStub::specificPerform()
{
    qDebug("Make money transaction!!!");
    return true;
}
