#include "Packet.h"
#include "PacketsList.h"

bool Packet::_isInited = false;
std::unordered_map<char, PacketHolder> Packet::_packetsMap;

void Packet::init()
{
    if(_isInited)
    {
        return;
    }
    qRegisterMetaType<PacketHolder>();
    _packetsMap[1] = PacketHolder(new UserAuthPacket());
    _isInited = true;
}

PacketHolder Packet::getPacket(char id, int descriptor)
{
    if(!_isInited)
    {
        init();
        _isInited = true;
    }
    for(std::unordered_map<char, PacketHolder>::iterator iterator = _packetsMap.begin();
        iterator != _packetsMap.end();
        ++iterator)
    {
        if(iterator->first == id)
        {
            PacketHolder pack = iterator->second->clone();
            pack->setSourceDescriptor(descriptor);
            return pack;
        }
    }
    return PacketHolder(NULL);
}

void Packet::setSourceDescriptor(int descriptor) const
{
    _socketDescriptor = descriptor;
}

void Packet::removeFirstPacket(QByteArray& data)
{
    if(isPacket(data))
    {
        unsigned int size = getPacketSize(data);
        data.remove(0,size+sizeof(char)+sizeof(short));
    }
}

bool Packet::isPacket(const QByteArray& byteArray)
{
    if(byteArray.length() < 3)
    {
        return false;
    }
    else
    {
        return getPacketSize(byteArray) <= (byteArray.length()-sizeof(char)-sizeof(short));
    }
}

char Packet::getPacketId(const QByteArray& byteArray)
{
    return *byteArray.data();
}

unsigned short Packet::getPacketSize(const QByteArray& byteArray)
{
    return *(reinterpret_cast<const unsigned short*>(byteArray.data()+1)); // + sizeof(char) + sizeof(short)
}

//virtual method

PacketHolder Packet::specificHandle() const
{
    return PacketHolder(NULL);
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
