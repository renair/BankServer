#include <QDebug>
#include <fstream>
#include <iostream>
using namespace std;

#include "DataBase/testingdb.h"
#include "DataBase/connection.h"
#include "DataBase/Objects/transfer.h"
#include "DataBase/Access/transfer_table.h"

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
    Connection* connection = new Connection();
    TransferTable transfers(*connection);
    ofstream out;
    out.open("res.txt");
    cout<< "File opened" <<endl;
    try{
        //out<< transfers.get_by_id(1) <<endl;
        out<< transfers.get_by_id(1) <<endl;
    }catch(const QString& error){
        out<< "Error: " + error.toStdString();
    }
    out.close();
    cout<< "Completed!" <<endl;
    delete connection;
    return;
}
