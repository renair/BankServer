#include "PacketStorage.h"
#include "../Protocol/Packet.h"

#include "QFile"

PacketStorage::PacketStorage():
    _saveFileName("pending_packets.bin")
{
    loadFromFile();
}

PacketStorage::PacketStorage(const QString& filename):
    _saveFileName(filename)
{
    loadFromFile();
}

PacketStorage::~PacketStorage()
{
    if(amount() > 0)
    {
        saveToFile();
    }
    while(!_packetsQueue.isEmpty())
    {
        delete _packetsQueue.dequeue();
    }
}

void PacketStorage::addPacket(Packet* p)
{
    _mutex.lock();
    _packetsQueue.enqueue(p);
    _mutex.unlock();
}

Packet* PacketStorage::nextPacket() const
{
    _mutex.lock();
    Packet* packet = _packetsQueue.dequeue();
    _mutex.unlock();
    return packet;
}

unsigned int PacketStorage::amount() const
{
    return _packetsQueue.size();
}

QString& PacketStorage::saveFileName()
{
    return _saveFileName;
}

const QString& PacketStorage::saveFileName() const
{
    return _saveFileName;
}

void PacketStorage::loadFromFile()
{
    loadFromFile(_saveFileName);
}

void PacketStorage::loadFromFile(const QString& filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QByteArray data = file.readAll();
    if(file.exists())
    {
        _mutex.lock();
        while(Packet::isPacket(data))
        {
            Packet* packet = Packet::getPacket(Packet::getPacketId(data));
            packet->load(data);
            _packetsQueue.enqueue(packet);
        }
        _mutex.unlock();
    }
}

void PacketStorage::saveToFile() const
{
    saveToFile(_saveFileName);
}

void PacketStorage::saveToFile(const QString& filename) const
{
    QFile file(filename);
    file.open(QFile::WriteOnly);
    //critical section - copy existed queue
    _mutex.lock();
    QQueue<Packet*> temp_queue(_packetsQueue);
    temp_queue.detachShared();
    _mutex.unlock();
    //end of critical section
    while(!temp_queue.isEmpty())
    {
        Packet* packet = temp_queue.dequeue();
        file.write(packet->dump());
    }
}
