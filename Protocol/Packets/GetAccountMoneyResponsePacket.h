#ifndef GETACCOUNTMONEYRESPONSEPACKET_H
#define GETACCOUNTMONEYRESPONSEPACKET_H

#include "../Packet.h"

class GetAccountMoneyResponsePacket : public Packet
{
private:
    // Fields.
    quint64 _accountId;
    quint64 _amount;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    GetAccountMoneyResponsePacket();
    GetAccountMoneyResponsePacket(quint64 accountId, quint64 amount);
    ~GetAccountMoneyResponsePacket();

    quint64& accountId()
    {
        return _accountId;
    }

    quint64& amount()
    {
        return _amount;
    }

    quint64 accountId() const
    {
        return _accountId;
    }

    quint64 amount() const
    {
        return _amount;
    }
};

#endif // GETACCOUNTMONEYRESPONSEPACKET_H
