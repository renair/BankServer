#include <QCoreApplication>
#include <iostream>
#include "Server/Server.h"
#include "AppClose.h"

#include "TaskPool/Tasks/PeriodicPaymentTask.h"

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    signal(SIGINT, &quitApp); //for aboutToQuit() work properly

    Server serv(ServerConfiguration("config.ini"));
    QObject::connect(&app, SIGNAL(aboutToQuit()), &serv, SLOT(stop()));
    try
    {
        serv.start();
    }
    catch(const QTcpSocket::SocketError& err)
    {
        cout << "Can't start server!" << endl;
        cout << "Reason: ";
        switch(err)
        {
        case QAbstractSocket::AddressInUseError:
            cout << "Address already in use.";
            break;
        case QAbstractSocket::SocketAccessError:
            cout << "You have no privilages to run server. Try root or administrative.";
            break;
        case QAbstractSocket::SocketResourceError:
            cout << "No available resources to start server.";
            break;
        case QAbstractSocket::NetworkError:
            cout << "Unexpected network error.";
            break;
        default:
            cout << "Unknown error. Code #" << err;
        }
        cout << endl;
    }

    return app.exec();
}
