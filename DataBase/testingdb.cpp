#include <iostream>
using namespace std;

#include "DataBase/testingdb.h"
#include "DataBase/connection.h"
#include "DataBase/Objects/Transfer.h"
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
    /*Transfer* t = new Transfer();
    cout<< *t <<endl;
    cout<< t->id() <<endl;
    t->id()=5;
    cout<< t->id() <<endl;
    delete t;*/
    Connection* connection = new Connection();
    TransferTable transfers(*connection);
    cout<< transfers.get_by_id(1) <<endl;
    delete connection;
    //Transfer t(1,1,"Some comments");
    //cout<<t<<endl;
    //Transfer t();
    return;
}
