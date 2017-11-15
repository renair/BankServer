#include "PacketBuilder.h"
#include "../Protocol/Packet.h"

PacketBuilder::PacketBuilder(PacketStorage& storage):
    _packetStorage(storage)
{}

PacketBuilder::~PacketBuilder()
{
    _packetStorage.saveToFile();
}

void PacketBuilder::buildAndPut(QByteArray& data, int socketDescriptor)
{
    while(Packet::isPacket(data))
    {
        PacketHolder pack = Packet::getPacket(Packet::getPacketId(data), socketDescriptor);
        pack->load(data);
        _packetStorage.addPacket(pack);
        Packet::removeFirstPacket(data);
    }
}
