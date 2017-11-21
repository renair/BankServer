#include <QThread>
#include <iostream>
#include "PacketProcessor.h"
#include "../Protocol/Packets/ErrorPacket.h"

using namespace std;

PacketProcessor::PacketProcessor():
    _receivedPackets("received_packets.pack")
{}

PacketProcessor::~PacketProcessor()
{
    _receivedPackets.saveToFile();
    cout << "Unprocessed packets saved to " << _receivedPackets.saveFileName().toStdString().c_str() << endl;
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
    cout << "Packet processor have been started" << endl; //LOG
    _isRunning = true;
    while(_isRunning)
    {
        if(_receivedPackets.amount() > 0)
        {
            PacketHolder packet = _receivedPackets.nextPacket();
            PacketHolder processed(NULL);
            try
            {
                processed = packet->handle();
                cout << "Packet ID#" << (int)packet->getID() << " from " << packet->sourceDescriptor() << " processed. "; //LOG
                cout << "Response with ID#" << (int)(processed ? processed->getID() : -100) << endl; //LOG
            }
            catch(...)
            {
                cout << "Unexpected exception during handling packet with ID#" << (int)packet->getID() << endl; //LOG
                processed = PacketHolder(new ErrorPacket("Unexpected server error"));
            }
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
    cout << "Packet processor have been stopped" << endl; //LOG
}
