#include <QDebug>
#include "GetCardsPacket.h"
#include "GetCardsResponsePacket.h"
#include "ErrorPacket.h"
#include "DataBase/Access/session_table.h"
#include "DataBase/Access/account_table.h"

#include <iostream>
using namespace std;

GetCardsPacket::GetCardsPacket():
    _token(0),
    _machineId(0),
    _userId(0)
{}

GetCardsPacket::GetCardsPacket(quint64 token, quint32 machineId ,quint64 userId):
    _token(token),
    _machineId(machineId),
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
    data.append((char*)&_machineId, sizeof(_machineId));
    data.append((char*)&_userId, sizeof(_userId));
    return data;
}

void GetCardsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_machineId, sizeof(_machineId));
    data.read((char*)&_userId, sizeof(_userId));
}

PacketHolder GetCardsPacket::specificHandle() const
{
    if(!SessionTable().renewSession(token(), machineId()))
    {
        return PacketHolder(new ErrorPacket("You are not authorized"));
    }
    GetCardsResponsePacket* response = new GetCardsResponsePacket();
    try
    {
        quint64 s = SessionTable().getUserBySignature(token());
        QMap<quint64, qint8> temp(AccountTable().getUserAccountsList(s));
        response->cards().swap(temp);
    }
    catch(const AccountTable::AccountTableError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const SessionTable::SessionTableError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const Connection::ConnectionError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    return PacketHolder(response);
}
