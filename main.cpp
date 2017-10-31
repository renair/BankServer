#include <QCoreApplication>
#include <iostream>
#include "Protocol/Packet.h"
#include "Protocol/Packets/UserAuthPacket.h"
#include "Server/Server.h"
#include "Server/PacketStorage.h"
#include "BankSystem/BankManager.h"
#include "DataBase/Objects/transfer.h"
#include "DataBase/testingdb.h"

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    PacketStorage* storage = new PacketStorage("testfile.bin");
//    for(int i = 5000000;i > 0; --i)
//    {
//        storage->addPacket(new UserAuthPacket());
//    }
    cout << "readed " << storage->amount() << " packets" << endl;
    cout << "saving to file" << endl;
    //storage->saveToFile();
    cout << "saved!" << endl;
    QThread::sleep(15);
    delete storage;
    cout << "storage deleted!" << endl;
    cout << "finished" << endl;

//    Server server;
//    server.start(2000);
//    {
//        TestingDB* test = new TestingDB();
//        test->run();
//        delete test;
//    }
    return a.exec();
}
