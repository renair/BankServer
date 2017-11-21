#include "Server.h"
#include "../Protocol/Packet.h"
#include <iostream>
#include <cassert>

using namespace std;

Server::Server():
    _packetBuilder(_packetProcessor.receivedPacket())
{
    makeConnections();
    _packetProcessor.moveToThread(&_processorThread);
}

Server::Server(const ServerConfiguration& config):
    _configuation(config),
    _packetBuilder(_packetProcessor.receivedPacket())
{
    makeConnections();
    _packetProcessor.moveToThread(&_processorThread);
}

Server::~Server()
{
    stop();
}

void Server::makeConnections() const
{
    //contains metatype registration(PacketHolder)
    Packet::init();
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    connect(&_processorThread, SIGNAL(started()), &_packetProcessor, SLOT(startProcessing()));
    connect(&_packetProcessor, SIGNAL(packetProcessed(PacketHolder)), this, SLOT(sendPacket(PacketHolder)), Qt::QueuedConnection); //will call async
}

void Server::start(unsigned short port)
{
    cout << "Starting server... " << endl; //LOG
    _processorThread.start();
    if(_tcpServer.isListening() || !_tcpServer.listen(QHostAddress::Any, port))
    {
        throw _tcpServer.serverError();
    }
    cout << "Server started." << endl; //LOG
}

void Server::stop()
{
    cout << "Stoping server..." << endl; //LOG
    //PacketProcessor will save all unprocessed packets
    _packetProcessor.stopProcessing();
    //close all opened connection
    for(QMap<int, QByteArray*>::const_iterator iterator = _connectionData.begin();
        iterator != _connectionData.end();
        iterator++)
    {
        delete iterator.value();
        _connectionSocket.take(iterator.key())->deleteLater();
    }

    assert(_connectionSocket.size() == 0);

    //close main server
    _tcpServer.close();
    cout << "\tdone";
}

void Server::clientConnected()
{
    while(_tcpServer.hasPendingConnections())
    {
        QTcpSocket* client = _tcpServer.nextPendingConnection();
        connect(client, SIGNAL(readyRead()), this , SLOT(dataReady()));
        connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        int peerPort = client->peerPort();
        _connectionData.insert(peerPort, new QByteArray());
        _connectionSocket.insert(peerPort, client);
        cout << "New client connected " << peerPort << endl; //LOG
    }
}

void Server::dataReady()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    QByteArray* data = _connectionData[caller->peerPort()];
    data->append(caller->readAll());
    _packetBuilder.buildAndPut(*data, caller->peerPort());
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    int peerPort = caller->peerPort();
    delete _connectionData.take(peerPort); //take - remove
    _connectionSocket.remove(peerPort);
    caller->deleteLater();
    cout << "Client disconnected " << peerPort << endl; //LOG
}

void Server::sendPacket(PacketHolder packet)
{
    int descriptor = packet->sourceDescriptor();
    if(_connectionSocket.contains(descriptor))
    {
        _connectionSocket[descriptor]->write(packet->dump());
    }
    else
    {
        cout << "There is no connection: " << descriptor << ". Skip packet ID#" << (int)packet->getID() << endl; //LOG
    }
}
