#include <QDebug>
#include "DataBase/connection.h"

Connection::Connection(QString type, QString name, QString address):
    _db_type(type),
    _db_name(name),
    _db_address(address)
{}

Connection::~Connection()
{}

Connection::Connection(Connection& c):
    _db_type(c.DBtype()),
    _db_name(c.DBname()),
    _db_address(c.DBaddress())
{}

bool Connection::open()
{
    _data_base = QSqlDatabase::addDatabase(_db_type);
    _data_base.setDatabaseName(_db_address+_db_name);
    return _data_base.open();
}

QSqlQuery Connection::execute(const QString& sql)
{
    /* TODO when open()==false */
    if(!open())
        throw QString("Cannot connect to data base");
    QSqlQuery q;
    q.exec(sql);
    return q;
}
