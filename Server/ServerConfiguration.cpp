#include "ServerConfiguration.h"

//default configuration
ServerConfiguration::ServerConfiguration():
    _waitingPacketsStorage("WaitingPackets.pack")
{}

ServerConfiguration::~ServerConfiguration(){}
