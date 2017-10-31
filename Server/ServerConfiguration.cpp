#include "ServerConfiguration.h"

ServerConfiguration::defaultConfiguration._waitingPacketsStorage = "WaitingPackets.pack";

ServerConfiguration::ServerConfiguration()
{
    *this = ServerConfiguration::defaultConfiguration;
}

ServerConfiguration::~ServerConfiguration(){}
