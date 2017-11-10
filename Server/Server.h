#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "PacketBuilder.h"
#include "PacketStorage.h"
#include "PacketProcessor.h"
#include "ServerConfiguration.h"
#include "Protocol/PacketsList.h"

class Server : QObject
{
    Q_OBJECT
private:
    QTcpServer _tcpServer;
    QMap<int, QByteArray *> _connectionsMap;
    ServerConfiguration _configuation;
    QThread _processorThread;
    PacketProcessor _packetProcessor;
    PacketBuilder _packetBuilder;
    void makeConnections() const;
    //deleted methods
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
public:
    Server();
    Server(const ServerConfiguration&);
    ~Server();
    void start(unsigned short port = 45654);
private slots:
    //slot for server
    void clientConnected();
    //slots for clients
    void dataReady();
    void clientDisconnected();
    void sendPacket(PacketHolder);
};

#endif // SERVER_H
