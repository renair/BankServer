#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include <QMap>
#include "PacketStorage.h"

class PacketProcessor : public QObject
{
    Q_OBJECT
private:
    PacketStorage _receivedPackets;
    PacketStorage _processedPackets;
    PacketProcessor& operator=(const PacketProcessor&) = delete;
    PacketProcessor(const PacketProcessor&) = delete;
public:
    PacketProcessor();
    ~PacketProcessor();
    PacketStorage& receivedPacket();
    const PacketStorage& receivedPacket() const;
    PacketStorage& processedPacket();
    const PacketStorage& processedPacket() const;
    void processPacket(PacketHolder&);
signals:
    void packetProcessed(PacketHolder packet);
};

#endif // PACKETPROCESSOR_H
