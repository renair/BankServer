#ifndef SUCCESSPACKET_H
#define SUCCESSPACKET_H

#include <string>
#include "../Packet.h"

class SuccessPacket : public Packet
{
private:
    std::string _message;
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    SuccessPacket(const std::string& msg = "");
    virtual ~SuccessPacket();

    //selectors-modifiers
    std::string& message()
    {
        return _message;
    }

    //selector
    const std::string& message() const
    {
        return _message;
    }
};

#endif // SUCCESSPACKET_H
