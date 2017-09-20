#include "Packet.h"
#include "PacketsList.h"

using namespace Protocol;

bool Packet::_isInited = false;
std::unordered_map<char, Packet*> Packet::_packetsMap;

void Packet::init()
{
    _packetsMap[1] = new UserAuthPacket();
}

Packet* Packet::getPacket(char id)
{
    if(!_isInited)
    {
        init();
    }
    for(std::unordered_map<char, Packet*>::iterator iterator = _packetsMap.begin();
        iterator != _packetsMap.end();
        ++iterator)
    {
        if(iterator->first == id)
        {
            return iterator->second->clone();
        }
    }
    return NULL;
}
