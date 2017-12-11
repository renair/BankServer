#include <chrono>
#include <iostream>
#include "PacketProcessor.h"
#include "../Protocol/Packets/ErrorPacket.h"

using namespace std;

PacketProcessor::PacketProcessor():
    _receivedPackets("received_packets.pack"),
    _isRunning(false),
    _finished(true),
    _thread(NULL)
{}

PacketProcessor::~PacketProcessor()
{
    stopProcessing();
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
    while(!_finished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete _thread;
    _thread = NULL;
}

void PacketProcessor::startProcessingLoop()
{
    cout << "Packet processor have been started" << endl; //LOG
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
            emit packetProcessed(processed);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); //wait half a second
        }
    }
    cout << "Packet processor have been stopped" << endl; //LOG
    _finished = true;
}

void PacketProcessor::startProcessing()
{
    if(_thread == NULL)
    {
        _isRunning = true;
        _finished = false;
        _thread = new std::thread(&PacketProcessor::startProcessingLoop, this);
        _thread->detach();
    }
}
