#ifndef MAKEPAYMENTRESPONSEPACKET_H
#define MAKEPAYMENTRESPONSEPACKET_H

#include "../Packet.h"

class MakePaymentResponsePacket : public Packet
{
public:
    MakePaymentResponsePacket();
    ~MakePaymentResponsePacket();
    enum PaymentStatus
    {
        PAYMENT_SUCCESSFULL = 1,
        NOT_ENOUGH_MONEY = 2,
        SERVER_ERROR = 3,
        UNKNOWN_ERROR = 10
    };
    void setPaymentStatus(PaymentStatus);
    PaymentStatus getPaymentStatus() const;
private:
    //fields
    char _paymentStatus;
    //method configuration
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    static PaymentStatus getStatusFromId(char);
};

#endif // MAKEPAYMENTRESPONSEPACKET_H
