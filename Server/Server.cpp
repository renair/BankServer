#include "Server.h"
#include "../Protocol/Packet.h"

Server::Server():
    _packetBuilder(_packetStorage)
{
    _packetStorage.saveFileName() = _configuation._waitingPacketsStorage;
    _packetStorage.loadFromFile();
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

    //TODO make one function!
    _packetProcessor.setResponsibility();
    _packetProcessor.registerProcessor(1, new UserAuthProcessor());
}

Server::Server(const ServerConfiguration& config):
    _configuation(config),
    _packetStorage(config._waitingPacketsStorage),
    _packetBuilder(_packetStorage)
{
    _packetStorage.loadFromFile();
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

    //TODO make one function!
    _packetProcessor.setResponsibility();
    _packetProcessor.registerProcessor(1, new UserAuthProcessor());
}

Server::~Server()
{
    //do some stuff before closing sockets
    _packetStorage.saveToFile();
    //delete all buffers
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
    while(_packetStorage.amount() > 0)
    {
        Packet* pack = _packetStorage.nextPacket();
        Packet* response = _packetProcessor.processPacket(pack);
        if(response != NULL)
        {
            caller->write(response->dump());
        }
        delete pack;
        delete response;
    }
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    caller->readAll();
    delete _connectionsMap[caller->socketDescriptor()];
    _connectionsMap.remove(caller->socketDescriptor());
}
