#ifndef USERAUTHPACKET_H
#define USERAUTHPACKET_H

#include "../Packet.h"
#include <QBuffer>

namespace Protocol
{
    class UserAuthPacket : public Packet
    {
    private:
        static const char _ID;
        long long _cardnum;
        short _password;
    public:
        UserAuthPacket();
        UserAuthPacket(long long card, short pass);
        UserAuthPacket(const UserAuthPacket&);
        //selectors-modifiers
        long long& card();
        short& password();
        //selectors
        long long card() const;
        short password() const;
        //interface methods
        char getID() const;
        Packet* clone() const;
        QByteArray dump() const;
        void load(QByteArray&);
        void handle() const;
    };
}

#endif // UserAuthPacket_H
