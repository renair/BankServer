#ifndef GETCARDSPACKET_H
#define GETCARDSPACKET_H

#include "../Packet.h"

class GetCardsPacket : public Packet
{
private:
    // Fields.
    quint64 _token;
    quint32 _machineId;
    quint64 _userId;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    virtual PacketHolder specificHandle() const;
public:
    GetCardsPacket();
    GetCardsPacket(quint64 token, quint32 machineId, quint64 userId);
    ~GetCardsPacket();

    // Selector-modifiers.
    quint64& token()
    {
        return _token;
    }

    quint32& machineId()
    {
        return _machineId;
    }

    quint64& userId()
    {
        return _userId;
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

    quint64 userId() const
    {
        return _userId;
    }
};

#endif // GETCARDSPACKET_H
