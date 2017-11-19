#ifndef ERRORPACKET_H
#define ERRORPACKET_H

#include "../Packet.h"

class ErrorPacket : public Packet
{
private:
    // Field.
    QString _info;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    ErrorPacket(const QString = "Unexpected error");
    ~ErrorPacket();

    // Selector-modifier.
    QString info()
    {
        return _info;
    }

    // Selector.
    const QString info() const
    {
        return _info;
    }
};

#endif // ERRORPACKET_H
