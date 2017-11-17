#include "atm.h"

ATM::ATM(quint64 id,
         const QString& address,
         uint uhr_10,
         uint uhr_20,
         uint uhr_50,
         uint uhr_100,
         uint uhr_200,
         uint uhr_500):
    _id(id),
    _address(address),
    _10_uhr(uhr_10),
    _20_uhr(uhr_20),
    _50_uhr(uhr_50),
    _100_uhr(uhr_100),
    _200_uhr(uhr_200),
    _500_uhr(uhr_500)
{}

ATM::~ATM(){}

uint ATM::add10uhr(uint count)
{
    if(_10_uhr<_10_uhr+count)
        throw ATMError("Out of range");
    return _10_uhr+=count;
}
uint ATM::add20uhr(uint count)
{
    if(_20_uhr<_20_uhr+count)
        throw ATMError("Out of range");
    return _20_uhr+=count;
}
uint ATM::add50uhr(uint count)
{
    if(_50_uhr<_50_uhr+count)
        throw ATMError("Out of range");
    return _50_uhr+=count;
}
uint ATM::add100uhr(uint count)
{
    if(_100_uhr<_100_uhr+count)
        throw ATMError("Out of range");
    return _100_uhr+=count;
}
uint ATM::add200uhr(uint count)
{
    if(_200_uhr<_200_uhr+count)
        throw ATMError("Out of range");
    return _200_uhr+=count;
}
uint ATM::add500uhr(uint count)
{
    if(_500_uhr<_500_uhr+count)
        throw ATMError("Out of range");
    return _500_uhr+=count;
}

uint ATM::take10uhr(uint count)
{
    if(count>_10_uhr)
        throw ATMError("Not enough money");
    return _10_uhr-=count;
}
uint ATM::take20uhr(uint count)
{
    if(count>_20_uhr)
        throw ATMError("Not enough money");
    return _20_uhr-=count;
}
uint ATM::take50uhr(uint count)
{
    if(count>_50_uhr)
        throw ATMError("Not enough money");
    return _50_uhr-=count;
}
uint ATM::take100uhr(uint count)
{
    if(count>_100_uhr)
        throw ATMError("Not enough money");
    return _100_uhr-=count;
}
uint ATM::take200uhr(uint count)
{
    if(count>_200_uhr)
        throw ATMError("Not enough money");
    return _200_uhr-=count;
}
uint ATM::take500uhr(uint count)
{
    if(count>_500_uhr)
        throw ATMError("Not enough money");
    return _500_uhr-=count;
}

ATM::ATMError::ATMError(const QString & reason): _reason(reason)
{}
