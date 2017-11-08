#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include "Packet.h"

//packet processor interface
class PacketProcessor
{
private:
    virtual PacketHolder specificPerform(PacketHolder&) = 0;
public:
    PacketHolder process(PacketHolder& p)
    {
        return specificPerform(p);
    }

    virtual ~PacketProcessor(){}
};

#endif // PACKETPROCESSOR_H
