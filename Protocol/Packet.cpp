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

bool Packet::isPacket(const QByteArray& byteArray)
{
    if(byteArray.length() < 3)
    {
        return false;
    }
    else
    {
        return getPacketSize(byteArray) == (byteArray.length()-sizeof(char)-sizeof(short));
    }
}

char Packet::getPacketId(const QByteArray& byteArray)
{
    return *byteArray.data();
}

unsigned short Packet::getPacketSize(const QByteArray& byteArray)
{
    return *(reinterpret_cast<const unsigned short*>(byteArray.data()+1));
}
