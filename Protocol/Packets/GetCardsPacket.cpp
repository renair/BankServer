#include "GetCardsPacket.h"

GetCardsPacket::GetCardsPacket():
    _token(0),
    _userId(0)
{}

GetCardsPacket::GetCardsPacket(const quint64 token, const quint64 userId):
    _token(token),
    _userId(userId)
{}

GetCardsPacket::~GetCardsPacket()
{}

char GetCardsPacket::specificGetID() const
{
    return 3;
}

PacketHolder GetCardsPacket::specificClone() const
{
    return PacketHolder(new GetCardsPacket(*this));
}

QByteArray GetCardsPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_userId, sizeof(_userId));
    return data;
}

void GetCardsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_userId, sizeof(_userId));
}

PacketHolder GetCardsPacket::specificHandle() const
{
    // TODO implement this method.
    // Must return -3 Packet.
    qDebug("GetCardsPacket is not implemented yet!");
    return PacketHolder(NULL);
}
