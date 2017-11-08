#include "Server.h"
#include "../Protocol/Packet.h"

Server::Server():
    _packetBuilder(_packetProcessor.receivedPacket())
{
    PacketStorage& stor = _packetProcessor.receivedPacket();
    stor.saveFileName() = _configuation._waitingPacketsStorage;
    stor.loadFromFile();
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

}

Server::Server(const ServerConfiguration& config):
    _configuation(config),
//    _receivedPackets(config._waitingPacketsStorage),
    _packetBuilder(_packetProcessor.receivedPacket())
{
//    _receivedPackets.loadFromFile();
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
}

Server::~Server()
{
//    do some stuff before closing sockets
//    _receivedPackets.saveToFile();
//    delete all buffers
    for(QMap<int, QByteArray*>::const_iterator iterator = _connectionsMap.begin();
        iterator != _connectionsMap.end();
        iterator++)
    {
        delete iterator.value();
    }
}

void Server::start(unsigned short port)
{
    if(_tcpServer.isListening() || !_tcpServer.listen(QHostAddress::Any, port))
    {
        throw _tcpServer.serverError();
    }
}

void Server::clientConnected()
{
    while(_tcpServer.hasPendingConnections())
    {
        QTcpSocket* client = _tcpServer.nextPendingConnection();
        connect(client, SIGNAL(readyRead()), this , SLOT(dataReady()));
        connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        _connectionsMap.insert(client->socketDescriptor(), new QByteArray());
    }
}

//TODO fix this absolutely INCORRECT code!
void Server::dataReady()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    QByteArray* callerData = _connectionsMap[caller->socketDescriptor()];
    callerData->append(caller->readAll());
    _packetBuilder.buildAndPut(*callerData);
    //TODO REPLACE WITH THREAD!!!
//    while(_receivedPackets.amount() > 0)
//    {
//        PacketHolder pack = _receivedPackets.nextPacket();
//        PacketHolder response = _packetProcessor.processPacket(pack);
//        if(response)
//        {
//            caller->write(response->dump());
//        }
//    }
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    caller->readAll();
    delete _connectionsMap[caller->socketDescriptor()];
    _connectionsMap.remove(caller->socketDescriptor());
}
