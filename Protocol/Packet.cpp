#include "Packet.h"
#include "PacketsList.h"
#include <iostream>

using namespace std;

bool Packet::_isInited = false;
QMap<char, PacketHolder> Packet::_packetsMap;

void Packet::init()
{
    if(_isInited)
    {
        return;
    }
    cout << "Initializing packets..."; //LOG
    qRegisterMetaType<PacketHolder>();
    //we needn't handle response packets
    _packetsMap[1] = PacketHolder(new UserAuthPacket());
//    _packetsMap[-1] = PacketHolder(new UserAuthResponsePacket());
    _packetsMap[2] = PacketHolder(new GetAccountMoneyPacket());
//    _packetsMap[-2] = PacketHolder(new GetAccountMoneyResponsePacket());
    _packetsMap[3] = PacketHolder(new GetCardsPacket());
//    _packetsMap[-3] = PacketHolder(new GetCardsResponsePacket());
    _packetsMap[4] = PacketHolder(new MakePaymentPacket());
//    _packetsMap[-4] = PacketHolder(new MakePaymentResponsePacket());
    _packetsMap[5] = PacketHolder(new GetPaymentsPacket());
//    _packetsMap[-5] = PacketHolder(new GetPaymentsResponsePacket());
    _packetsMap[6] = PacketHolder(new UserLogoutPacket());
//    _packetsMap[7] = PacketHolder(new SuccessPacket());
    _packetsMap[8] = PacketHolder(new CancelPeriodicPaymentPacket());
    _isInited = true;
    cout << "\tdone" << endl; //LOG
}

PacketHolder Packet::getPacket(char id, int descriptor)
{
    if(!_isInited)
    {
        init();
    }
    if(_packetsMap.contains(id))
    {
        PacketHolder pack = _packetsMap[id]->clone();
        pack->setSourceDescriptor(descriptor);
        return pack;
    }
    return PacketHolder(NULL);
}

void Packet::setSourceDescriptor(int descriptor)
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
