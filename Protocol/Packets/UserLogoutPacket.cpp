#include "UserLogoutPacket.h"
#include "ErrorPacket.h"

UserLogoutPacket::UserLogoutPacket(quint64 token, quint32 machineId):
    _token(token),
    _machineId(machineId)
{}

UserLogoutPacket::~UserLogoutPacket()
{}

char UserLogoutPacket::specificGetID() const
{
    return 6;
}

PacketHolder UserLogoutPacket::specificClone() const
{
    return PacketHolder(new UserLogoutPacket(*this));
}

QByteArray UserLogoutPacket::specificDump() const
{
    QByteArray res;
    res.append((char*)&_token, sizeof(_token));
    res.append((char*)&_machineId, sizeof(_machineId));
    return res;
}

void UserLogoutPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_token, sizeof(_token));
    buff.read((char*)&_machineId, sizeof(_machineId));
}

PacketHolder UserLogoutPacket::specificHandle() const
{
    //TODO implement method
    return PacketHolder(new ErrorPacket("Method not supported now."));
}
