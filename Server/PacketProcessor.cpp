#include "PacketProcessor.h"

PacketProcessor::PacketProcessor():
    _receivedPackets("received_packets.pack"),
    _processedPackets("processed_packets.pack")
{}

PacketProcessor::~PacketProcessor()
{
    _receivedPackets.saveToFile();
    _processedPackets.saveToFile();
}

PacketStorage& PacketProcessor::receivedPacket()
{
    return _receivedPackets;
}

const PacketStorage& PacketProcessor::receivedPacket() const
{
    return _receivedPackets;
}

PacketStorage& PacketProcessor::processedPacket()
{
    return _processedPackets;
}

const PacketStorage& PacketProcessor::processedPacket() const
{
    return _processedPackets;
}

void PacketProcessor::processPacket(PacketHolder& pack)
{
    PacketHolder processed = pack->handle();
    //_processedPackets.addPacket(processed);
    emit packetProcessed(processed);
}
