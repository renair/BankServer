#ifndef GETCARDSRESPONSEPACKET_H
#define GETCARDSRESPONSEPACKET_H

#include <QMap>
#include "../Packet.h"

class GetCardsResponsePacket : public Packet
{
private:
    // Fields.
    QMap<quint64, quint8> _cards;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    GetCardsResponsePacket();
    ~GetCardsResponsePacket();

    // Selectors-modifiers.
    QMap<quint64, quint8>& cards()
    {
        return _cards;
    }

    // Selectors.
    quint8 amount() const
    {
        return _cards.size();
    }

    const QMap<quint64, quint8>& cards() const
    {
        return _cards;
    }
};

#endif // GETCARDSRESPONSEPACKET_H
