#ifndef USERAUTHRESPONSEPACKET_H
#define USERAUTHRESPONSEPACKET_H

#include "../Packet.h"

class UserAuthResponsePacket : public Packet
{
private:
    //fields
    QString _token;
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    UserAuthResponsePacket();
    UserAuthResponsePacket(const QString&);
    ~UserAuthResponsePacket();
    inline QString& token()
    {
        return _token;
    }
    inline QString token() const
    {
        return _token;
    }
};

#endif // USERAUTHRESPONSEPACKET_H
