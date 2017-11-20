#include <QDebug>
#include "GetCardsPacket.h"
#include "GetCardsResponsePacket.h"
#include "ErrorPacket.h"
#include "DataBase/Access/session_table.h"
#include "DataBase/Access/account_table.h"

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
    if(!SessionTable().renewSession(token()))
        return PacketHolder(new ErrorPacket("You are not authorized"));
    GetCardsResponsePacket* response = new GetCardsResponsePacket();
    try
    {
        response->cards() = AccountTable().getUserAccountsList(
                    SessionTable().getUserBySignature(token()));
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
