#include "Server.h"

using namespace std;

Server::Server()
{
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
}

Server::~Server()
{
    //do some stuff before closing sockets
    for(vector<QTcpSocket*>::const_iterator iterator = _connections.begin();
        iterator != _connections.end();
        iterator++)
    {
        QTcpSocket* sock = *iterator;
        if(sock->isOpen())
        {
            sock->close();
        }
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
        _connections.push_back(client);
    }
}

void Server::dataReady()
{
    //test stub!
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    char data[1024];
    int length = caller->read(data, 1024);
    caller->write(data, length);
}

void Server::clientDisconnected()
{
    QTcpSocket* caller = static_cast<QTcpSocket*>(sender());
    caller->readAll();
    for(vector<QTcpSocket*>::const_iterator iterator = _connections.begin();
        iterator != _connections.end();
        iterator++)
    {
        if(*iterator == caller)
        {
            _connections.erase(iterator);
            return;
        }
    }
}
