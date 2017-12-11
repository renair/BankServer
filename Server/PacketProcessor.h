#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include <QMap>
#include <thread>
#include "PacketStorage.h"

class PacketProcessor : public QObject
{
    Q_OBJECT
private:
    PacketStorage _receivedPackets;
    bool _isRunning;
    bool _finished;
    std::thread* _thread;
    PacketProcessor& operator=(const PacketProcessor&) = delete;
    PacketProcessor(const PacketProcessor&) = delete;
    void startProcessingLoop();
public:
    PacketProcessor();
    ~PacketProcessor();
    PacketStorage& receivedPacket();
    const PacketStorage& receivedPacket() const;
//    PacketStorage& processedPacket();
//    const PacketStorage& processedPacket() const;
    void processPacket(PacketHolder&);
    bool isRunning() const;
public slots:
    void startProcessing();
    void stopProcessing();
signals:
    void packetProcessed(PacketHolder packet);
};

#endif // PACKETPROCESSOR_H
