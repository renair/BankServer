#include <QDebug>
#include <fstream>
#include <iostream>
using namespace std;

#include "DataBase/testingdb.h"
#include "DataBase/connection.h"
#include "DataBase/Objects/transfer.h"
#include "DataBase/Access/transfer_table.h"
#include "DataBase/Objects/user.h"
#include "DataBase/Access/user_table.h"
#include "DataBase/Objects/withdraw.h"
#include "DataBase/Access/withdraw_table.h"
#include "DataBase/Objects/account.h"

TestingDB::TestingDB()
{
    return;
}

TestingDB::~TestingDB()
{
    return;
}

void TestingDB::run()
{
    cout<< "Test db connection" <<endl;
    Connection::getConnection();
//    Connection* connection = &conn;//= new Connection();
//    cout<< "Is connected: " << Connection::getConnection().connect() <<endl;
//    TransferTable transfers(Connection::getConnection());
//    UserTable users(Connection::getConnection());
    UserTable users;
    //WithdrawTable withdraws(connection);
//    ofstream out;
//    out.open("res.txt");
//    cout<< "File opened" <<endl;
    try{
//        Account acc(1,1,1,"1234",1);
//        cout<< acc.id() <<endl;
//        quint64 max(-1);
//        quint64 next(max+1);
//        while (next>max)
//        {
//            max=next;
//            if((max%1000000000)==0)
//                cout<< max/1000000000 << "mlrd - ";
//            ++next;
//        }
//        cout<< "max: " << max <<endl;
//        quint32 b(max);
//        quint32 c(b+1);
//        cout<< "b: " << b <<endl<< "b+1: " << c <<endl;
//        out<< transfers.get_by_id(1) <<endl;
//        cout<< transfers.getById(1) <<endl;
//        quint64 upid(5553575000);
//        cout<< "Original num: " << upid <<endl;
//        cout<< "QString num:  " << QString::number(upid).toStdString() <<endl;
//        cout<< users.get_by_upid(upid) <<endl;
        User u(1,"pass","CT555","MyName","MySurname","MyFatherName",5553535);
        cout<< "Is created new user: " << users.create_new(u) <<endl;
        u.name()="NewName1";
//        cout<< "User 1: " << users.get_by_upid(1) <<endl;
        cout<< "Is updated: " << users.update(u) <<endl;
//        Withdraw w(1,1,155,"wth","comm");
//        withdraws.create_new(w);
        //cout<< "User password: " << u.password() <<endl;
    }catch(const UserTable::UserTableError& error){
        cout<< "Error: " + error.reason().toStdString() <<endl;
    }
//    out.close();
//    cout<< "Completed!" <<endl;
    return;
}
