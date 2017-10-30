#ifndef PACKETSTORAGE_H
#define PACKETSTORAGE_H

#include <QQueue>
#include <QMutex>

class Packet;

class PacketStorage
{
private:
    QQueue<Packet*> _paketsQueue;
    QString _saveFileName;
    QMutex _mutex;
    PacketStorage(const PacketStorage&) = delete;
    PacketStorage& operator=(const PacketStorage&) = delete;
public:
    PacketStorage();
    PacketStorage(const QString&);
    ~PacketStorage();
    void addPacket(Packet*);
    Packet* nextPacket() const;
    unsigned int amount() const;
    void loadFromFile();
    void loadFromFile(const QSrting&);
    void saveToFile() const;
    void saveToFile(const QString&);
};

#endif // PACKETSTORAGE_H
