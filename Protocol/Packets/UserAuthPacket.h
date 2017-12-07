#ifndef USERAUTHPACKET_H
#define USERAUTHPACKET_H

#include "../Packet.h"
#include <QBuffer>

class UserAuthPacket : public Packet
{
private:
    static const char _ID;
    quint64 _cardNumber;
    QString _password;
    quint32 _machineId;

    //interface methods
    char specificGetID() const;
    PacketHolder specificClone() const;
    QByteArray specificDump() const;
    void specificLoad(QBuffer&);
    PacketHolder specificHandle() const;
public:
    UserAuthPacket();
    UserAuthPacket(quint64 card, const QString& pass, quint32 machineId);
    //selectors-modifiers
    quint64& card();
    QString& password();
    quint32& machineId();
    //selectors
    quint64 card() const;
    const QString& password() const;
    quint32 machineId() const;
};


#endif // UserAuthPacket_H
