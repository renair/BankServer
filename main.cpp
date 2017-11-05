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
#include "Protocol/Processors/UserAuthProcessor.h"
#include "Server/PacketProcessorCenter.h"

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    Server serv;
    serv.start();

//    PacketProcessor* proc = new UserAuthProcessor();
//    Packet* pack = new UserAuthPacket();

//    PacketProcessorCenter center(false); //not responsible center
//    center.registerProcessor(pack->getID(), proc);

//    center.processPacket(pack);
//    cout << center.isResponsible() << endl;
//    center.setResponsibility();
//    cout << center.isResponsible() << endl;
//    cout << center.processorsAmount() << endl;

//    center.setResponsibility(false);
//    delete pack;
//    delete proc;

//    Server server;
//    server.start(2000);
//    {
//        TestingDB* test = new TestingDB();
//        test->run();
//        delete test;
//    }
    return a.exec();
}
