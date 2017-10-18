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

// Methods from NVI

QByteArray Packet::dump() const
{
    QByteArray data = specificDump(); //using pure virtual method
    QByteArray result;
    result.append(getID());
    unsigned short size = data.length();
    result.append((char*)&size, sizeof(short));
    result.append(data);
    return result;
}

void Packet::load(QByteArray& byteArray)
{
    QBuffer buff(&byteArray);
    buff.open(QBuffer::ReadOnly);
    char i = 0;
    buff.read(&i, sizeof(i));
    if(i != getID())
    {
        //throw some error
    }
    buff.seek(buff.pos()+sizeof(short)); //skip size field
    specificLoad(buff);
}
