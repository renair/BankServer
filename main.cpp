#include <QCoreApplication>
#include <iostream>
#include "Protocol/Packet.h"
#include "Protocol/Packets/UserAuthPacket.h"
#include "Server/Server.h"
#include "Server/PacketStorage.h"
#include "BankSystem/BankManager.h"
#include "DataBase/Objects/transfer.h"
#include "DataBase/testingdb.h"
#include "Server/PacketBuilder.h"
#include "Server/PacketProcessor.h"

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

//    Server serv;
//    serv.start(45654);

    {
        TestingDB* test = new TestingDB();
        test->run();
        delete test;
    }
    return a.exec();
}
