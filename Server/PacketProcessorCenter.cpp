#include "PacketProcessorCenter.h"

PacketProcessorCenter::PacketProcessorCenter(bool responsibility):
    _isResponsible(responsibility)
{}

PacketProcessorCenter::~PacketProcessorCenter()
{
    if(isResponsible())
    {
        for(QMap<char, PacketProcessor*>::Iterator obj = _registeredProcessors.begin();
            obj != _registeredProcessors.end();
            obj++)
        {
            delete obj.value();
        }
    }
}

bool PacketProcessorCenter::isResponsible() const
{
    return _isResponsible;
}

void PacketProcessorCenter::setResponsibility(bool responsibility)
{
    _isResponsible = responsibility;
}

unsigned int PacketProcessorCenter::processorsAmount() const
{
    return _registeredProcessors.size();
}

PacketProcessor* PacketProcessorCenter::getPacketProcessor(char id)
{
    return _registeredProcessors.contains(id) ? _registeredProcessors[id] : NULL;
}

const PacketProcessor* PacketProcessorCenter::getPacketProcessor(char id) const
{
    return _registeredProcessors.contains(id) ? _registeredProcessors[id] : NULL;
}

void PacketProcessorCenter::registerProcessor(char id, PacketProcessor* processor)
{
    if(isResponsible())
    {
        delete getPacketProcessor(id);
    }
    _registeredProcessors[id] = processor;
}

PacketHolder PacketProcessorCenter::processPacket(PacketHolder& pack)
{
    PacketProcessor* processor = getPacketProcessor(pack->getID());
    return processor != NULL ? processor->process(pack) : NULL;
}
