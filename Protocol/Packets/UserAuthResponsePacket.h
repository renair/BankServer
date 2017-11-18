#ifndef USERAUTHRESPONSEPACKET_H
#define USERAUTHRESPONSEPACKET_H

#include "../Packet.h"

class UserAuthResponsePacket : public Packt
{
private:
    //fields
    quint64 _token;
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    UserAuthResponsePacket();
    UserAuthResponsePacket(quint64);
    ~UserAuthResponsePacket();
    inline quint64& token()
    {
        return _token;
    }
    inline quint64 token() const
    {
        return _token;
    }
};

#endif // USERAUTHRESPONSEPACKET_H
