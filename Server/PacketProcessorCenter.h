#ifndef PACKETPROCESSORCENTER_H
#define PACKETPROCESSORCENTER_H

#include <QMap>
#include "../Protocol/PacketProcessor.h"
#include "../Protocol/Packet.h"

class PacketProcessorCenter
{
private:
    QMap<char, PacketProcessor*> _registeredProcessors;
    //if PacketProcessorCenter is responsive it delete packets after using it
    bool _isResponsible;
    PacketProcessorCenter& operator=(const PacketProcessorCenter&) = delete;
    PacketProcessorCenter(const PacketProcessorCenter&) = delete;
public:
    PacketProcessorCenter(bool responsive = true);
    ~PacketProcessorCenter();
    bool isResponsible() const;
    void setResponsibility(bool r = true);
    unsigned int processorsAmount() const;
    PacketProcessor* getPacketProcessor(char);
    const PacketProcessor* getPacketProcessor(char) const;
    void registerProcessor(char, PacketProcessor*);
    void processPacket(Packet*);
};

#endif // PACKETPROCESSORCENTER_H
