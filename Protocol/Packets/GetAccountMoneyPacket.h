#ifndef GETACCOUNTSMONEY_H
#define GETACCOUNTSMONEY_H

#include "../Packet.h"

class GetAccountMoneyPacket : public Packet
{
private:
    // Fields.
    quint64 _token;
    quint32 _machineId;
    quint64 _accountId;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    virtual PacketHolder specificHandle() const;
public:
    GetAccountMoneyPacket();
    GetAccountMoneyPacket(quint64 token, quint32 machineId, quint64 accountId);
    ~GetAccountMoneyPacket();

    // Selector-modifiers.
    quint64& token()
    {
        return _token;
    }

    quint32& machineId()
    {
        return _machineId;
    }

    quint64& accountId()
    {
        return _accountId;
    }

    // Selectors.
    quint64 token() const
    {
        return _token;
    }

    quint32 machineId() const
    {
        return _machineId;
    }

    quint64 accountId() const
    {
        return _accountId;
    }
};

#endif // GETACCOUNTSMONEY_H
