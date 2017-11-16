#ifndef GETACCOUNTMONEYRESPONSEPACKET_H
#define GETACCOUNTMONEYRESPONSEPACKET_H

#include "../Packet.h"

class GetAccountMoneyResponsePacket : public Packet
{
public:
    GetAccountMoneyResponsePacket();
    GetAccountMoneyResponsePacket(quint64 accountId, quint64 amount);
    ~GetAccountMoneyResponsePacket();
private:
    // Fields.
    quint64 _accountId;
    quint64 _amount;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
};

#endif // GETACCOUNTMONEYRESPONSEPACKET_H
