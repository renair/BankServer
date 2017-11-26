#include <QCoreApplication>
#include <iostream>
#include "Server/Server.h"

//#include "DataBase/testingdb.h"
//#include "DataBase/Access/account_table.h"
//#include "DataBase/Access/user_table.h"
//#include "Protocol/PacketsList.h"
//#include "DataBase/Access/session_table.h"
//#include <QDateTime>
using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    Server serv;
    QObject::connect(&app, SIGNAL(aboutToQuit()), &serv, SLOT(stop()));
    try
    {
        serv.start(45654);
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
