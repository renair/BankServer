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

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    PacketProcessor* proc = new UserAuthProcessor();
    Packet* pack = new UserAuthPacket();

    proc->process(pack);

    delete pack;
    delete proc;

//    PacketStorage* storage = new PacketStorage("testfile.bin");
//    append packets to the file! loading become slower!!!
//    for(int i = 500;i > 0; --i)
//    {
//        storage->addPacket(new UserAuthPacket());
//    }
//    cout << "readed " << storage->amount() << " packets" << endl;
//    cout << "saving to file" << endl;
//    storage->saveToFile();
//    cout << "saved!" << endl;
//    QThread::sleep(15);
//    delete storage;
//    cout << "storage deleted!" << endl;
//    cout << "finished" << endl;

//    Server server;
//    server.start(2000);
//    {
//        TestingDB* test = new TestingDB();
//        test->run();
//        delete test;
//    }
    return a.exec();
}
