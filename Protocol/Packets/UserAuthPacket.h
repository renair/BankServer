#ifndef USERAUTHPACKET_H
#define USERAUTHPACKET_H

#include "../Packet.h"
#include <QBuffer>

class UserAuthPacket : public Packet
{
private:
    static const char _ID;
    long long _cardNumber;
    QString _password;

    //interface methods
    char specificGetID() const;
    PacketHolder specificClone() const;
    QByteArray specificDump() const;
    void specificLoad(QBuffer&);
    PacketHolder specificHandle() const;
public:
    UserAuthPacket();
    UserAuthPacket(long long card, short pass);
    UserAuthPacket(const UserAuthPacket&);
    //selectors-modifiers
    long long& card();
    QString& password();
    //selectors
    long long card() const;
    const QString& password() const;
};


#endif // UserAuthPacket_H
