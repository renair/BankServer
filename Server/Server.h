#ifndef SERVER_H
#define SERVER_H

#include <QtGlobal> //to include qintptr
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>

class Server : QObject
{
    Q_OBJECT
private:
    QTcpServer _tcpServer;
    QMap<qintptr, QByteArray*> _connectionsMap;
    //deleted methods
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
public:
    Server();
    ~Server();
    void start(unsigned short port = 45654);
private slots:
    //slot for server
    void clientConnected();
    //slots for clients
    void dataReady();
    void clientDisconnected();
};

#endif // SERVER_H
