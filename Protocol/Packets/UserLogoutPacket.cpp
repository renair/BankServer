#include "UserLogoutPacket.h"
#include "ErrorPacket.h"
#include "DataBase/Access/session_table.h"

#include <iostream>
using namespace std;

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
    cout<< "logout" <<endl;
    SessionTable sessionTable;
    Session session = sessionTable.getBySignature(token());
    if(session.atmId()!=machineId()) return PacketHolder(new ErrorPacket("Unexpected error in relation to session ID and machine ID."));
    quint64 time = QDateTime::currentDateTime().toTime_t();
    session.renewValidTime(time);
    sessionTable.update(session);
    return PacketHolder(0);
}
