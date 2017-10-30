#include "Server.h"
#include "../Protocol/Packet.h"

using namespace std;

Server::Server()
{
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
}

Server::~Server()
{
    //do some stuff before closing sockets
    for(QMap<int, QByteArray*>::const_iterator iterator = _connectionsMap.begin();
        iterator != _connectionsMap.end();
        iterator++)
    {
        delete iterator.value();
    }
}

void Server::start(unsigned short port)
{
    if(!_tcpServer.listen(QHostAddress::Any, port))
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

void Server::dataReady()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    QByteArray* callerData = _connectionsMap[caller->socketDescriptor()];
    callerData->append(caller->readAll());
    if(Packet::isPacket(*callerData))
    {
        //do some stuff
        Packet* p = Packet::getPacket(1);
        p->load(*callerData);
        //callerData->re
    }
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    caller->readAll();
    delete _connectionsMap[caller->socketDescriptor()];
    _connectionsMap.remove(caller->socketDescriptor());
}
