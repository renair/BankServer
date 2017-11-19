#include <QDebug>
#include "GetAccountMoneyPacket.h"
#include "GetAccountMoneyResponsePacket.h"
#include "ErrorPacket.h"
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
    Account acc;
    try
    {
        acc = AccountTable().getById(accountId());
    }
    catch(const AccountTable::AccountTableError& err)
    {
        return PacketHolder(new ErrorPacket (err.reason()));
    }
    catch(const Connection::ConnectionError& err)
    {
        return PacketHolder(new ErrorPacket(err.reason()));
    }
    return PacketHolder(new GetAccountMoneyResponsePacket(acc.id(),acc.moneyAmount()));
}
