#include <QSettings>
#include "ServerConfiguration.h"

//default configuration
ServerConfiguration::ServerConfiguration():
    _configurationFile("BankServerConfig.ini")
{
    loadConfiguration(_configurationFile);
}

ServerConfiguration::ServerConfiguration(const QString& filename):
    _configurationFile(filename)
{
    loadConfiguration(filename);
}

ServerConfiguration::~ServerConfiguration()
{
    saveConfiguration(_configurationFile);
}

void ServerConfiguration::loadConfiguration(const QString& filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    _waitingPacketsStorage = settings.value("packets_storage", "WaitingPackets.pack").toString();
    _serverPort = settings.value("port", 45654).toInt();
}

void ServerConfiguration::loadConfiguration(const QString& filename) const
{
    QSettings settings(filename, QSettings::IniFormat);
    _waitingPacketsStorage = settings.value("packets_storage", "WaitingPackets.pack").toString();
    _serverPort = settings.value("port", 45654).toInt();
}

void ServerConfiguration::saveConfiguration(const QString& filename) const
{
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("packets_storage", _waitingPacketsStorage);
    settings.setValue("port", _serverPort);
}
