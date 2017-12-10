#include <QDebug>
#include "GetPaymentsPacket.h"
#include "GetPaymentsResponsePacket.h"
#include "ErrorPacket.h"
#include "DataBase/Access/session_table.h"
#include "DataBase/Access/transfer_table.h"

GetPaymentsPacket::GetPaymentsPacket():
    _token(0),
    _machineId(0),
    _cardNumber(0)
{}

GetPaymentsPacket::GetPaymentsPacket(quint64 token, quint32 machineId, quint64 carnNum):
    _token(token),
    _machineId(machineId),
    _cardNumber(carnNum)
{}

GetPaymentsPacket::~GetPaymentsPacket()
{}

char GetPaymentsPacket::specificGetID() const
{
    return 5;
}

PacketHolder GetPaymentsPacket::specificClone() const
{
    return PacketHolder(new GetPaymentsPacket(*this));
}

QByteArray GetPaymentsPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_machineId, sizeof(_machineId));
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    return data;
}

void GetPaymentsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_machineId, sizeof(_machineId));
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
}

PacketHolder GetPaymentsPacket::specificHandle() const
{
    if(!SessionTable().renewSession(token(), machineId()))
    {
        return PacketHolder(new ErrorPacket("You are not authorized"));
    }
    GetPaymentsResponsePacket* response = new GetPaymentsResponsePacket();
    try
    {
        QList<Transfer> list = TransferTable().getTransfersFromAccount(cardNumber());
        for(int i = 0;i < list.size();++i)
        {
            response->addPayment(list[i].receiverId(), list[i].amount());
        }
    }
    catch(const TransferTable::TransferTableError& err)
    {
        delete response;
        return PacketHolder(new ErrorPacket (err.reason()));
    }
    catch(const Connection::ConnectionError& err)
    {
        delete response;
        return PacketHolder(new ErrorPacket (err.reason()));
    }
    return PacketHolder(response);
}
