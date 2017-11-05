#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

class Packet;

//packet processor interface
class PacketProcessor
{
private:
    virtual Packet* specificPerform(Packet*) = 0;
public:
    Packet* process(Packet* p)
    {
        return specificPerform(p);
    }

    virtual ~PacketProcessor(){}
};

#endif // PACKETPROCESSOR_H
