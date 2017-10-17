#ifndef PACKET_H
#define PACKET_H

#include<unordered_map>
#include<QByteArray>

namespace Protocol
{
    class Packet
    {
    private:
        static std::unordered_map<char, Packet*> _packetsMap;
        static bool _isInited;
        static void init();
    public:
        static Packet* getPacket(char id);
        static bool isPacket(const QByteArray&);
        static char getPacketId(const QByteArray&);
        static unsigned short getPacketSize(const QByteArray&);
        //interface methods
        virtual char getID() const = 0;
        virtual Packet* clone() const = 0;
        virtual QByteArray dump() const = 0;
        virtual void load(QByteArray&) = 0;
        virtual void handle() const = 0;
    };
}

#endif // PACKET_H
