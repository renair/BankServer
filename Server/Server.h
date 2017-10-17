#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server : QObject
{
    Q_OBJECT
private:
    QTcpServer _tcpServer;
    QMap<int, QTcpSocket*> _connectionMap;
public:
    Server(int port = 45654);
    ~Server();
    void start() const;
    //deleted methods
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
private slots:
    void newConnection();
};

#endif // SERVER_H
