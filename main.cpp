#include <QCoreApplication>
#include <iostream>
#include "Protocol/Packet.h"
#include "Server/Server.h"

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    Server server;
    server.start(2000);
    return a.exec();
}
