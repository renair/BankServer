#include <QDebug>
#include "GetAccountMoneyPacket.h"
#include "GetAccountMoneyResponsePacket.h"
#include "DataBase/Objects/account.h"
#include "DataBase/Access/account_table.h"

GetAccountMoneyPacket::GetAccountMoneyPacket():
    _token(0),
    _accountId(0)
{}

GetAccountMoneyPacket::GetAccountMoneyPacket
    (const quint64 token, const quint64 accountId):
    _token(token),
    _accountId(accountId)
{}

GetAccountMoneyPacket::~GetAccountMoneyPacket()
{}

char GetAccountMoneyPacket::specificGetID() const
{
    return 2;
}

PacketHolder GetAccountMoneyPacket::specificClone() const
{
    return PacketHolder(new GetAccountMoneyPacket(*this));
}

QByteArray GetAccountMoneyPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_accountId, sizeof(_accountId));
    return data;
}

void GetAccountMoneyPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_accountId, sizeof(_accountId));
}

PacketHolder GetAccountMoneyPacket::specificHandle() const
{
    // TODO implement this method.
    // Must return -2 Packet.
    AccountTable accounts;
    Account acc;
    try
    {
        acc = accounts.getById(accountId());
    }
    catch(const AccountTable::AccountTableError& error)
    {
        qDebug()<< error.reason();
    }
    catch(const Connection::ConnectionError& error)
    {
        qDebug()<< error.reason();
    }

    GetAccountMoneyResponsePacket response(acc.id(),acc.moneyAmount());
//    qDebug("GetAccountMoneyPacket is not implemented yet!");
    return PacketHolder(&response);
}
