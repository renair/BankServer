#include <QDebug>
#include <QDateTime>
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
#include "DataBase/Access/account_table.h"

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
//    Clearing database
    {
        Connection::getConnection().
               execute("DELETE \
                        FROM payment \
                        WHERE ID IN (SELECT ID \
                                     FROM payment);");
        Connection::getConnection().
               execute("DELETE \
                        FROM account \
                        WHERE ID IN (SELECT ID \
                                     FROM account);");
        Connection::getConnection().
               execute("DELETE \
                        FROM cash_machine \
                        WHERE id IN (SELECT id \
                                     FROM cash_machine);");
        Connection::getConnection().
               execute("DELETE \
                        FROM session \
                        WHERE signature IN (SELECT signature \
                                            FROM session);");
        Connection::getConnection().
               execute("DELETE \
                        FROM user \
                        WHERE UPID IN (SELECT UPID \
                                       FROM user);");
    }
//    User
    {
        UserTable users;
        User u1(1,"pass1","CT000001","1_name","1_surname","1_father_name",960000001);
        User u2(2,"pass2","CT000002","2_name","2_surname","2_father_name",960000002);
        try
        {
            users.createNew(u1);
            users.createNew(u2);
            users.getByUpid(u1.upid());
            users.getByUpid(u2.upid());
            u1.name()="New name";
            u2.surname()="New surname";
            if(u1.setNewPass("new_pass","pass2"))
                users.update(u1);
            if(u2.setNewPass("new_pass","pass2"))
                users.update(u2);
        }
        catch(const UserTable::UserTableError& error)
        {
            qDebug()<< error.reason();
        }
        catch(const Connection::ConnectionError& error)
        {
            qDebug()<< error.reason();
        }

    }
//    Account
    {
        AccountTable accounts;
        Account acc1(1,1,1,"pin1",10);
        Account acc2(2,1,2,"pin1",1000);
        Account acc3(3,1,3,"pin1",100);
        Account acc4(4,2,1,"pin2",0);
        try
        {
            accounts.createNew(acc1);
            accounts.createNew(acc2);
            accounts.createNew(acc3);
            accounts.createNew(acc4);
            cout<< "connected: " << Connection::getConnection().connected() <<endl;
        }
        catch(const AccountTable::AccountTableError& error)
        {
            qDebug()<<error.reason();
        }
        catch(const Connection::ConnectionError& error)
        {
            qDebug()<< error.reason();
        }
    }
    return;
}
