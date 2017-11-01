#include "UserAuthProcessor.h"
#include "../Packets/UserAuthPacket.h"

#include <qdebug.h>

UserAuthProcessor::UserAuthProcessor()
{
    qDebug("User processor created!");
}

UserAuthProcessor::~UserAuthProcessor()
{
    qDebug("User processor destroyed!");
}

//TODO add it to the sessions, etc.
void UserAuthProcessor::specificPerform(Packet* p)
{
    const UserAuthPacket* packet = static_cast<const UserAuthPacket*>(p); //cast to needed type
    long long num = packet->card();
    short pas = packet->password();
}
