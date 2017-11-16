#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "PacketStorage.h"

class PacketBuilder
{
private:
    PacketStorage& _packetStorage;

    PacketBuilder(const PacketBuilder&) = delete;
    PacketBuilder& operator=(const PacketBuilder&) = delete;
public:
    PacketBuilder(PacketStorage&);
    ~PacketBuilder();
    void buildAndPut(QByteArray&, int);
};

#endif // PACKETBUILDER_H
