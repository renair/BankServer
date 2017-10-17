#include "Server.h"
#include "../Protocol/Packet.h"

using namespace std;
using namespace Protocol;

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
        connect(client, SIGNAL(disconnected()), this, SLOT(clientConnected()));
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
    }
    //test stub!
//    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
//    char data[1024];
//    int length = caller->read(data, 1024);
//    caller->write(data, length);
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    caller->readAll();
    delete _connectionsMap[caller->socketDescriptor()];
    _connectionsMap.remove(caller->socketDescriptor());
}
