#ifndef ATM_H
#define ATM_H

#include <QString>

class ATM
{
public:
    ATM(quint64 id=0,
        const QString& address="",
        uint uhr_10=0,
        uint uhr_20=0,
        uint uhr_50=0,
        uint uhr_100=0,
        uint uhr_200=0,
        uint uhr_500=0);
    ~ATM();
    quint64 id() const {return _id;}
    const QString& address() const {return _address;}
    uint uhr_10() const {return _10_uhr;}
    uint uhr_20() const {return _20_uhr;}
    uint uhr_50() const {return _50_uhr;}
    uint uhr_100() const {return _100_uhr;}
    uint uhr_200() const {return _200_uhr;}
    uint uhr_500() const {return _500_uhr;}

    QString& address() {return _address;}
    uint add10uhr(uint count);
    uint add20uhr(uint count);
    uint add50uhr(uint count);
    uint add100uhr(uint count);
    uint add200uhr(uint count);
    uint add500uhr(uint count);

    uint take10uhr(uint count);
    uint take20uhr(uint count);
    uint take50uhr(uint count);
    uint take100uhr(uint count);
    uint take200uhr(uint count);
    uint take500uhr(uint count);
private:
    quint64 _id;
    QString _address;
    uint _10_uhr;
    uint _20_uhr;
    uint _50_uhr;
    uint _100_uhr;
    uint _200_uhr;
    uint _500_uhr;
public:
    class ATMError
    {
    public:
        ATMError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;
        ATMError();
    };
};

#endif // ATM_H
