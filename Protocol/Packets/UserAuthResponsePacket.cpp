#include "UserAuthResponsePacket.h"

UserAuthResponsePacket::UserAuthResponsePacket()
{}

UserAuthResponsePacket::UserAuthResponsePacket(const QString& token):
    _token(token)
{}

UserAuthResponsePacket::~UserAuthResponsePacket()
{}

char UserAuthResponsePacket::specificGetID() const
{
    return -1;
}

PacketHolder UserAuthResponsePacket::specificClone() const
{
    return PacketHolder(new UserAuthResponsePacket(*this));
}

QByteArray UserAuthResponsePacket::specificDump() const
{
    QByteArray data;
    data.append(_token);
    return data;
}

void UserAuthResponsePacket::specificLoad(QBuffer& buffer)
{
    buffer.read(sizeof(_token));
}
