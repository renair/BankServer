#include "GetPaymentsPacket.h"

GetPaymentsPacket::GetPaymentsPacket()
{}

GetPaymentsPacket::~GetPaymentsPacket()
{}

char GetPaymentsPacket::specificGetID() const
{
    return 5;
}

PacketHolder GetPaymentsPacket::specificClone() const
{
    return PacketHolder(new GetPaymentsPacket(*this));
}

QByteArray GetPaymentsPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    return data;
}

void GetPaymentsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
}

PacketHolder GetPaymentsPacket::specificHandle() const
{
    //TODO implement it!
    qWarning("GetPaymentsPacket handling not implemented yet!");
    return PacketHolder(NULL);
}
