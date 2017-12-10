#ifndef GETPAYMENTSPACKET_H
#define GETPAYMENTSPACKET_H

#include "../Packet.h"

class GetPaymentsPacket : public Packet
{
private:
    //fields
    quint64 _token;
    quint32 _machineId;
    quint64 _cardNumber;
    //method setup
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    virtual PacketHolder specificHandle() const;
public:
    GetPaymentsPacket();
    GetPaymentsPacket(quint64 token, quint32 machineId, quint64 carnNum);
    ~GetPaymentsPacket();
    //selector-modifiers
    quint64& token()
    {
        return _token;
    }

    quint32& machineId()
    {
        return _machineId;
    }

    quint64& cardNumber()
    {
        return _cardNumber;
    }

    //selectors
    quint64 token() const
    {
        return _token;
    }

    quint32 machineId() const
    {
        return _machineId;
    }

    quint64 cardNumber() const
    {
        return _cardNumber;
    }
};

#endif // GETPAYMENTSPACKET_H
