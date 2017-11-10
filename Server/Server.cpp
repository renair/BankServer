#include "Server.h"
#include "../Protocol/Packet.h"

Server::Server():
    _packetBuilder(_packetProcessor.receivedPacket())
{
    PacketStorage& stor = _packetProcessor.receivedPacket();
    stor.saveFileName() = _configuation._waitingPacketsStorage;
    stor.loadFromFile();
    makeConnections();
    _packetProcessor.moveToThread(&_processorThread);
    _processorThread.start();
}

Server::Server(const ServerConfiguration& config):
    _configuation(config),
    _packetBuilder(_packetProcessor.receivedPacket())
{
    makeConnections();
    _packetProcessor.moveToThread(&_processorThread);
    _processorThread.start();
}

Server::~Server()
{
//    do some stuff before closing sockets
//    _receivedPackets.saveToFile();
//    delete all buffers
    _processorThread.exit();
    for(QMap<int, QByteArray*>::const_iterator iterator = _connectionsMap.begin();
        iterator != _connectionsMap.end();
        iterator++)
    {
        delete iterator.value();
    }
}

void Server::makeConnections() const
{
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    connect(&_processorThread, SIGNAL(started()), &_packetProcessor, SLOT(startProcessing()));
    connect(&_processorThread, SIGNAL(finished()), &_packetProcessor, SLOT(stopProcessing()));
    connect(&_packetProcessor, SIGNAL(packetProcessed(PacketHolder)), this, SLOT(sendPacket(PacketHolder)));
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

void Server::sendPacket(PacketHolder)
{
    qDebug("Sending response packet.");
}
