#ifndef SERVERCONFIGURATION_H
#define SERVERCONFIGURATION_H

#include <QString>

class ServerConfiguration
{
private:
    QString _configurationFile;
    //configuration parameters
    mutable QString _waitingPacketsStorage;
    mutable quint16 _serverPort;
    //private methods
    void loadConfiguration(const QString&) const;
public:
    ServerConfiguration();
    ServerConfiguration(const QString&);
    ~ServerConfiguration();
    void loadConfiguration(const QString&);
    void saveConfiguration(const QString&) const;
    //selectors-modifiers
    inline QString& packetStorage()
    {
        return _waitingPacketsStorage;
    }

    inline quint16& serverPort()
    {
        return _serverPort;
    }

    //selectors
    inline const QString& packetStorage() const
    {
        return _waitingPacketsStorage;
    }
    inline quint16 serverPort() const
    {
        return _serverPort;
    }
};

#endif // SERVERCONFIGURATION_H
