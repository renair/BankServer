#include <QCoreApplication>
#include <iostream>
#include "Protocol/Packet.h"
#include "Protocol/Client/UserAuthPacket.h"
#include "Server/Server.h"
#include "BankSystem/PaymentManager.h"
#include "DataBase/Objects/PaymentStub.h"

using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    Payment* p1 = new PaymentStub(100);
    Payment* p2 = new PaymentStub(200);
    Payment* p3 = new PaymentStub(300);
    Payment* p4 = new PaymentStub(400);
    Payment* p5 = new PaymentStub(500);

    PaymentManager manager;
    manager.addPayment(p1);
    manager.addPayment(p2);
    manager.addPayment(p3);
    manager.addPayment(p4);
    manager.addPayment(p5);

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
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
