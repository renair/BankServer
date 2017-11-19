#include "ErrorPacket.h"

ErrorPacket::ErrorPacket(const QString info):
    _info(info)
{}

ErrorPacket::~ErrorPacket()
{}

char ErrorPacket::specificGetID() const
{
    return 0;
}

PacketHolder ErrorPacket::specificClone() const
{
    return PacketHolder(new ErrorPacket(*this));
}

QByteArray ErrorPacket::specificDump() const
{
    return QByteArray()
            .append(_info.toStdString().c_str(), _info.length());
}

void ErrorPacket::specificLoad(QBuffer& data)
{
    _info = QString(data.readAll());
}
