#include "UserAuthProcessor.h"
#include "../Packets/UserAuthPacket.h"

UserAuthProcessor::UserAuthProcessor()
{
    qDebug("User processor created!");
}

UserAuthProcessor::~UserAuthProcessor()
{
    qDebug("User processor destroyed!");
}

//TODO add it to the sessions, etc.
PacketHolder UserAuthProcessor::specificPerform(PacketHolder& p)
{
    const UserAuthPacket* packet = static_cast<const UserAuthPacket*>(p.data()); //cast to needed type
    long long num = packet->card();
    short pas = packet->password();
    return NULL;
}
