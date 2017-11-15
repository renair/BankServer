#ifndef PACKET_H
#define PACKET_H

#include<QBuffer>
#include<QSharedPointer>
#include<unordered_map>

class Packet;

typedef QSharedPointer<Packet> PacketHolder;
Q_DECLARE_METATYPE(PacketHolder)

class Packet
{
private:
    static std::unordered_map<char, PacketHolder> _packetsMap;
    static bool _isInited;
    // specific methods for each packets
    virtual char specificGetID() const = 0;
    virtual PacketHolder specificClone() const = 0;
    virtual QByteArray specificDump() const = 0;
    virtual void specificLoad(QBuffer&) = 0;
    virtual PacketHolder specificHandle() const;
protected:
    // socket descriptor
    mutable int _socketDescriptor;
    void setSourceDescriptor(int)const;
public:
    virtual ~Packet(){}
    static void init();
    static PacketHolder getPacket(char id, int descriptor);
    static void removeFirstPacket(QByteArray&);
    static bool isPacket(const QByteArray&);
    static char getPacketId(const QByteArray&);
    static unsigned short getPacketSize(const QByteArray&);
    // NVI (NonVirtualInterface)
    QByteArray dump() const;
    void load(QByteArray& arr);

    inline int sourceDescriptor() const
    {
        return _socketDescriptor;
    }

    inline char getID() const
    {
        return specificGetID();
    }

    inline PacketHolder clone() const
    {
        PacketHolder pack = specificClone();
        pack->setSourceDescriptor(sourceDescriptor());
        return pack;
    }

    inline PacketHolder handle() const
    {
        return specificHandle();
    }
};


#endif // PACKET_H
