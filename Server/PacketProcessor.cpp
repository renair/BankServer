#include <QThread>
#include "PacketProcessor.h"

PacketProcessor::PacketProcessor():
    _receivedPackets("received_packets.pack")
{}

PacketProcessor::~PacketProcessor()
{
    _receivedPackets.saveToFile();
}

PacketStorage& PacketProcessor::receivedPacket()
{
    return _receivedPackets;
}

const PacketStorage& PacketProcessor::receivedPacket() const
{
    return _receivedPackets;
}


void PacketProcessor::processPacket(PacketHolder& pack)
{
    _receivedPackets.addPacket(pack);
}

bool PacketProcessor::isRunning() const
{
    return _isRunning;
}

void PacketProcessor::stopProcessing()
{
    _isRunning = false;
}

void PacketProcessor::startProcessing()
{
    _isRunning = true;
    while(_isRunning)
    {
        if(_receivedPackets.amount() > 0)
        {
            PacketHolder processed = _receivedPackets.nextPacket()->handle();
            if(processed)
            {
                    emit packetProcessed(processed);
            }
        }
        else
        {
            QThread::msleep(500); //wait half a second
        }
    }
}
