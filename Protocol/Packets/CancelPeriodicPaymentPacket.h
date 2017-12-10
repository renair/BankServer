#ifndef CANCELPERIODICPAYMENTPACKET_H
#define CANCELPERIODICPAYMENTPACKET_H

#include "../Packet.h"

class CancelPeriodicPaymentPacket : public Packet
{
private:
    //variables
    quint64 _token;
    quint64 _machineId;
    quint64 _paymentId;
    //NVI methods
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    virtual PacketHolder specificHandle() const;
public:
    CancelPeriodicPaymentPacket(quint64 t = 0, quint64 mi = 0, quint64 pi = 0);
    ~CancelPeriodicPaymentPacket();

    //selectors-modifiers
    quint64& token()
    {
        return _token;
    }

    quint64& machineId()
    {
        return _machineId;
    }

    quint64& paymentId()
    {
        return _paymentId;
    }

    //selectors
    quint64 token() const
    {
        return _token;
    }

    quint64 machineId() const
    {
        return _machineId;
    }

    quint64 paymentId() const
    {
        return _paymentId;
    }
};

#endif // CANCELPERIODICPAYMENTPACKET_H
