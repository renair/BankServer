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
    Connection connection;
//    Connection* connection = &conn;//= new Connection();
    cout<< "Is connected: " << connection.connect() <<endl;
    TransferTable transfers(connection);
    UserTable users(connection);
//    ofstream out;
//    out.open("res.txt");
//    cout<< "File opened" <<endl;
    try{
//        out<< transfers.get_by_id(1) <<endl;
        cout<< transfers.get_by_id(1) <<endl;
        quint64 upid(5553575000);
//        cout<< "Original num: " << upid <<endl;
//        cout<< "QString num:  " << QString::number(upid).toStdString() <<endl;
        cout<< users.get_by_upid(upid) <<endl;
        User u(1,"pass","CT555","MyName","MySurname","MyFatherName",5553535);
        //cout<< "Is created new user: " << users.create_new(u) <<endl;
        u.name()="NewName";
        cout<< "Is updated: " << users.update(u) <<endl;
        //cout<< "User password: " << u.password() <<endl;
    }catch(const QString& error){
        cout<< "Error: " + error.toStdString() <<endl;
    }
//    out.close();
//    cout<< "Completed!" <<endl;
    return;
}
