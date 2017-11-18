#include <QDebug>
#include "GetPaymentsPacket.h"
#include "GetPaymentsResponsePacket.h"
#include "DataBase/Access/transfer_table.h"

GetPaymentsPacket::GetPaymentsPacket()
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
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    return data;
}

void GetPaymentsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
}

PacketHolder GetPaymentsPacket::specificHandle() const
{
    //TODO implement it!
    TransferTable transfers;
    GetPaymentsResponsePacket response;
    try
    {
        QList<Transfer> list = transfers.getTransfersFromAccount(cardNumber());
        for(int i=0;i<list.size();++i)
        {
            response.addPayment(list[i].receiverId(),list[i].amount());
        }
    }
    catch(const TransferTable::TransferTableError& error)
    {
        qDebug()<< error.reason();
    }
    catch(const Connection::ConnectionError& error)
    {
        qDebug()<< error.reason();
    }
    qWarning("GetPaymentsPacket handling not implemented yet!");
    return PacketHolder(&response);
}
