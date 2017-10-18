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

        //interface methods
        char specificGetID() const;
        Packet* specificClone() const;
        QByteArray specificDump() const;
        void specificLoad(QBuffer&);
        void specificHandle() const;
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
    };
}

#endif // UserAuthPacket_H
