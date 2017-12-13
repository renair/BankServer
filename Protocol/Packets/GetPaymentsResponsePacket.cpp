#include "GetPaymentsResponsePacket.h"

GetPaymentsResponsePacket::GetPaymentsResponsePacket():
    _paymentsAmount(0)
{}

GetPaymentsResponsePacket::~GetPaymentsResponsePacket()
{}

void GetPaymentsResponsePacket::addPayment(quint64 paymentId, quint64 to, quint64 amount)
{
    _paymentsFields.append((char*)&paymentId, sizeof(paymentId));
    _paymentsFields.append((char*)&to, sizeof(to));
    _paymentsFields.append((char*)&amount, sizeof(amount));
    _paymentsAmount++;
}

char GetPaymentsResponsePacket::specificGetID() const
{
    return -5;
}

PacketHolder GetPaymentsResponsePacket::specificClone() const
{
    return PacketHolder(new GetPaymentsResponsePacket(*this));
}

QByteArray GetPaymentsResponsePacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_paymentsAmount, sizeof(_paymentsAmount));
    data.append(_paymentsFields);
    return data;
}

void GetPaymentsResponsePacket::specificLoad(QBuffer& data)
{
    _paymentsFields.clear();
    data.read((char*)&_paymentsAmount, sizeof(_paymentsAmount));
    for(quint16 i = 0; i < paymentsAmount();++i)
    {
        //read payment id
        _paymentsFields.append(data.read(sizeof(quint64)));
        //read card number
        _paymentsFields.append(data.read(sizeof(quint64)));
        //read money amount
        _paymentsFields.append(data.read(sizeof(quint64)));
    }
}
