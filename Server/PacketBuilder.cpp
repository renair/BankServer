#include "PacketBuilder.h"
#include "../Protocol/Packet.h"

PacketBuilder::PacketBuilder(PacketStorage& storage):
    _packetStorage(storage)
{}

PacketBuilder::~PacketBuilder()
{
    _packetStorage.saveToFile();
}

void PacketBuilder::buildAndPut(QByteArray& data)
{
    if(Packet::isPacket(data))
    {
        Packet* pack = Packet::getPacket(Packet::getPacketId(data));
        pack->load(data);
        _packetStorage.addPacket(pack);
        Packet::removeFirstPacket(data);
    }
}
