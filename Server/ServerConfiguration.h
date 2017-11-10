#ifndef SERVERCONFIGURATION_H
#define SERVERCONFIGURATION_H

#include <QString>

struct ServerConfiguration
{
    QString _waitingPacketsStorage;

    ServerConfiguration();
    ~ServerConfiguration();
};

#endif // SERVERCONFIGURATION_H
