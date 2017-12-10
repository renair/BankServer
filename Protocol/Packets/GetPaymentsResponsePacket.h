#ifndef GETPAYMENTSRESPONSEPACKET_H
#define GETPAYMENTSRESPONSEPACKET_H

#include "../Packet.h"

class GetPaymentsResponsePacket : public Packet
{
    //fields
    quint16 _paymentsAmount;
    QByteArray _paymentsFields; //TODO make selectors-modifiers
    //methods setup
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    GetPaymentsResponsePacket();
    ~GetPaymentsResponsePacket();
    quint16 paymentsAmount() const
    {
        return _paymentsAmount;
    }

    quint64& paymentId(quint16 i)
    {
        i = std::min(i, _paymentsAmount);
        return *(reinterpret_cast<quint64*>(_paymentsFields.data()+((i*3)*sizeof(quint64))));
    }

    quint64& to(quint16 i)
    {
        i = std::min(i, _paymentsAmount);
        return *(reinterpret_cast<quint64*>(_paymentsFields.data()+((i*3+1)*sizeof(quint64))));
    }

    quint64& amount(quint16 i)
    {
        i = std::min(i, _paymentsAmount);
        return *(reinterpret_cast<quint64*>(_paymentsFields.data()+((i*3+2)*sizeof(quint64))));
    }

    quint64 paymentId(quint16 i) const
    {
        i = std::min(i, _paymentsAmount);
        return *(reinterpret_cast<const quint64*>(_paymentsFields.data()+((i*3)*sizeof(quint64))));
    }

    quint64 to(quint16 i) const
    {
        i = std::min(i, _paymentsAmount);
        return *(reinterpret_cast<const quint64*>(_paymentsFields.data()+((i*3+1)*sizeof(quint64))));
    }

    quint64 amount(quint16 i) const
    {
        i = std::min(i, _paymentsAmount);
        return *(reinterpret_cast<const quint64*>(_paymentsFields.data()+((i*3+2)*sizeof(quint64))));
    }

    void addPayment(quint64 paymentId, quint64 to, quint64 amount);
};

#endif // GETPAYMENTSRESPONSEPACKET_H
