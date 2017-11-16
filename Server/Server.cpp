#include "Server.h"
#include "../Protocol/Packet.h"

#include <iostream>
using namespace std;

Server::Server():
    _packetBuilder(_packetProcessor.receivedPacket())
{
    Packet::init();
    makeConnections();
    _packetProcessor.moveToThread(&_processorThread);
    _processorThread.start();
}

Server::Server(const ServerConfiguration& config):
    _configuation(config),
    _packetBuilder(_packetProcessor.receivedPacket())
{
    Packet::init();
    makeConnections();
    _packetProcessor.moveToThread(&_processorThread);
    _processorThread.start();
}

Server::~Server()
{
    _processorThread.exit();
    for(QMap<int, QByteArray*>::const_iterator iterator = _connectionData.begin();
        iterator != _connectionData.end();
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
    connect(&_packetProcessor, SIGNAL(packetProcessed(PacketHolder)), this, SLOT(sendPacket(PacketHolder)), Qt::QueuedConnection); //will call async
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
        _connectionData.insert(client->socketDescriptor(), new QByteArray());
        _connectionSocket.insert(client->socketDescriptor(), client);
        cout << "New client connected " << client->socketDescriptor() << endl;
    }
}

void Server::dataReady()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    QByteArray* callerData = _connectionData[caller->socketDescriptor()];
    callerData->append(caller->readAll());
    _packetBuilder.buildAndPut(*callerData, caller->socketDescriptor());
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    caller->readAll();
    int descriptor = caller->socketDescriptor();
    delete _connectionData[descriptor];
    _connectionData.remove(descriptor);
    delete _connectionSocket[descriptor];
    _connectionSocket.remove(descriptor);
    cout << "Client disconnected " << descriptor << endl;
}

void Server::sendPacket(PacketHolder packet)
{
    int descriptor = packet->sourceDescriptor();
    if(descriptor != 0 && _connectionSocket.contains(descriptor))
    {
        QTcpSocket* socket = _connectionSocket[descriptor];
        socket->write(packet->dump());
        cout << "packed" << packet->getID() << " have been sent to " << descriptor << endl;
    }
}
