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
    std::string str = _info.toStdString();
    return QByteArray().append(str.c_str(), str.length()+1);
}

void ErrorPacket::specificLoad(QBuffer& data)
{
    _info = QString(data.readAll());
}
