#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "PacketBuilder.h"
#include "PacketStorage.h"
#include "PacketProcessor.h"
#include "ServerConfiguration.h"
#include "../TaskPool/TasksPool.h"

class Server : public QObject
{
    Q_OBJECT
private:
    bool _isStarted;
    QTcpServer _tcpServer;
    QMap<int, QByteArray*> _connectionData;
    QMap<int, QTcpSocket*> _connectionSocket;
    ServerConfiguration _configuation;
    PacketProcessor _packetProcessor;
    PacketBuilder _packetBuilder;
    TasksPool _tasksPool;

    void makeConnections() const;
    //deleted methods
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
public:
    Server();
    Server(const ServerConfiguration&);
    ~Server();
    void start();
    void start(quint16);
    void configureServer(const ServerConfiguration&);
    void addNewTask(const AbstractTask&);
public slots:
    void stop();
private slots:
    //slot for server
    void clientConnected();
    //slots for clients
    void dataReady();
    void clientDisconnected();
    void sendPacket(PacketHolder);
};

#endif // SERVER_H
