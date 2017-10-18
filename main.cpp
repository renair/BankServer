#include <QCoreApplication>
#include <iostream>
#include "Protocol/Packet.h"
#include "Protocol/Client/UserAuthPacket.h"
#include "Server/Server.h"

using namespace std;

int main(int argc, char** argv)
{
//    QCoreApplication a(argc, argv);
//    Protocol::UserAuthPacket p;
//    p.card() = 12432423425;
//    p.password() = 6294;

//    cout << boolalpha << Protocol::Packet::isPacket(p.dump()) << endl;
//    cout << (int)Protocol::Packet::getPacketId(p.dump()) << endl;
//    cout << Protocol::Packet::getPacketSize(p.dump()) << endl;

//    Server server;
//    server.start(2000);
    return a.exec();
}
