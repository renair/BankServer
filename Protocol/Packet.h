#ifndef PACKET_H
#define PACKET_H

#include<QBuffer>
#include<QSharedPointer>
#include<unordered_map>

class Packet;

typedef QSharedPointer<Packet> PacketHolder;

class Packet
{
private:
    static std::unordered_map<char, PacketHolder> _packetsMap;
    static bool _isInited;
    static void init();
    // specific methods for each packets
    virtual char specificGetID() const = 0;
    virtual PacketHolder specificClone() const = 0;
    virtual QByteArray specificDump() const = 0;
    virtual void specificLoad(QBuffer&) = 0;
    virtual PacketHolder specificHandle() const;
public:
    virtual ~Packet(){}
    static PacketHolder getPacket(char id);
    static void removeFirstPacket(QByteArray&);
    static bool isPacket(const QByteArray&);
    static char getPacketId(const QByteArray&);
    static unsigned short getPacketSize(const QByteArray&);
    // NVI (NonVirtualInterface)
    QByteArray dump() const;
    void load(QByteArray& arr);

    inline char getID() const
    {
        return specificGetID();
    }

    inline PacketHolder clone() const
    {
        return specificClone();
    }

    inline PacketHolder handle() const
    {
        return specificHandle();
    }
};


#endif // PACKET_H
