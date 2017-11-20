#include "PacketStorage.h"
#include "../Protocol/Packet.h"
#include <QFile>

PacketStorage::PacketStorage():
    _saveFileName("pending_packets.bin"),
    _isSaved(true)
{
    loadFromFile();
}

PacketStorage::PacketStorage(const QString& filename):
    _saveFileName(filename),
    _isSaved(true)
{
    loadFromFile();
}

PacketStorage::~PacketStorage()
{
    if(amount() > 0)
    {
        saveToFile();
    }
    _packetsQueue.clear(); //QSharedPtr will delete packets
}

void PacketStorage::addPacket(PacketHolder p)
{
    _mutex.lock();
    _packetsQueue.enqueue(p);
    _isSaved = false;
    _mutex.unlock();
}

PacketHolder PacketStorage::nextPacket() const
{
    PacketHolder packet(NULL);
    _mutex.lock();
    if(_packetsQueue.length() > 0)
    {
        packet = _packetsQueue.dequeue();
        _isSaved = false;
    }
    _mutex.unlock();
    return packet;
}

unsigned int PacketStorage::amount() const
{
    return _packetsQueue.size();
}

bool PacketStorage::isSaved() const
{
    return _isSaved;
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

//TODO improve loading algorithm!!!
void PacketStorage::loadFromFile(const QString& filename)
{
    QFile file(filename);
    if(file.exists())
    {
        file.open(QFile::ReadOnly);
        QByteArray data = file.readAll();
        _mutex.lock();
        while(Packet::isPacket(data))
        {
            PacketHolder packet = Packet::getPacket(Packet::getPacketId(data), 0);
            if(packet)
            {
                packet->load(data);
                _packetsQueue.enqueue(packet);
            }
            Packet::removeFirstPacket(data);
        }
        _isSaved = true;
        file.close();
        file.remove();
        _mutex.unlock();
    }
}

void PacketStorage::saveToFile() const
{
    saveToFile(_saveFileName);
}

void PacketStorage::saveToFile(const QString& filename) const
{
    if(!isSaved())
    {
        QFile file(filename);
        file.open(QFile::WriteOnly);
        //critical section - copy existed queue
        _mutex.lock();
        QQueue<PacketHolder> temp_queue(_packetsQueue);
        temp_queue.detachShared();
        _mutex.unlock();
        //end of critical section
        while(!temp_queue.isEmpty())
        {
            PacketHolder packet = temp_queue.dequeue();
            file.write(packet->dump());
            file.flush();
        }
        file.close();
        _isSaved = true;
    }
}
