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
    void addPayment(quint64 to, quint64 amount);
};

#endif // GETPAYMENTSRESPONSEPACKET_H
