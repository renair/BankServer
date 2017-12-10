#include "GetCardsResponsePacket.h"

GetCardsResponsePacket::GetCardsResponsePacket()
{}

GetCardsResponsePacket::~GetCardsResponsePacket()
{}

char GetCardsResponsePacket::specificGetID() const
{
    return -3;
}

PacketHolder GetCardsResponsePacket::specificClone() const
{
    return PacketHolder(new GetCardsResponsePacket(*this));
}

QByteArray GetCardsResponsePacket::specificDump() const
{
    QByteArray data;
    quint8 _amount = amount();
    data.append((char*)&_amount, sizeof(_amount));

    QMapIterator<quint64, qint8> iter(_cards);
    while (iter.hasNext())
    {
        iter.next();
        data.append((char*)&iter.key(), sizeof(iter.key()));
        data.append((char*)&iter.value(), sizeof(iter.value()));
    }
    return data;
}

void GetCardsResponsePacket::specificLoad(QBuffer& data)
{
    quint8 _amount = 0;
    data.read((char*)&_amount, sizeof(_amount));
    _cards.clear();
    for(int i = 0;i < _amount;++i)
    {
        quint64 card = 0;
        data.read((char*)&card, sizeof(card));
        qint8 type = 0;
        data.read((char*)&type, sizeof(type));
        _cards[card] = type;
    }
}
