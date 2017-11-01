#ifndef PACKETSTORAGE_H
#define PACKETSTORAGE_H

#include <QQueue>
#include <QMutex>

class Packet;

class PacketStorage
{
private:
    QString _saveFileName;
    mutable QQueue<Packet*> _packetsQueue;
    mutable QMutex _mutex;
    mutable bool _isSaved;
    PacketStorage(const PacketStorage&) = delete;
    PacketStorage& operator=(const PacketStorage&) = delete;
public:
    PacketStorage();
    PacketStorage(const QString&);
    ~PacketStorage();
    void addPacket(Packet*);
    Packet* nextPacket() const;
    unsigned int amount() const;
    bool isSaved() const;
    QString& saveFileName();
    const QString& saveFileName() const;
    void loadFromFile();
    void loadFromFile(const QString&);
    void saveToFile() const;
    void saveToFile(const QString&) const;
};

#endif // PACKETSTORAGE_H
