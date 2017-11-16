#include "MakePaymentPacket.h"

MakePaymentPacket::MakePaymentPacket()
{}

MakePaymentPacket::~MakePaymentPacket()
{}

char MakePaymentPacket::specificGetID() const
{
    return 4;
}

PacketHolder MakePaymentPacket::specificClone() const
{
    return PacketHolder(new MakePaymentPacket(*this));
}

QByteArray MakePaymentPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_from, sizeof(_from));
    data.append((char*)&_to, sizeof(_to));
    data.append((char*)&_amount, sizeof(_amount));
    data.append(_comment.toStdString().c_str(), _comment.toStdString().length());
    return data;
}

void MakePaymentPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_from, sizeof(_from));
    data.read((char*)&_to, sizeof(_to));
    data.read((char*)&_amount, sizeof(_amount));
    _comment = QString(data.readAll());
}

PacketHolder MakePaymentPacket::specificHandle() const
{
    //TODO implement this method
    //  Must return -4 Packet
    qDebug("MakePaymentPacket doesnt implemented yet!");
    return PacketHolder(NULL);
}
