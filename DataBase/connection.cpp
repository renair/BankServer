#include <QDebug>
#include <QFileInfo>
#include "DataBase/connection.h"

Connection Connection::_connection;

Connection::Connection(const QString& type, const QString& name, const QString& address):
    _db_type(type),
    _db_name(name),
    _db_address(address),
    _data_base(),
    _connected(false)
{
    _data_base = QSqlDatabase::addDatabase(_db_type);
    _data_base.setDatabaseName(_db_address+_db_name);
//    qDebug()<<"Connection constructor, _connected: " << _data_base.isOpen() <<endl;
}

Connection::~Connection()
{
    _data_base.close();
}

bool Connection::reconnect(const QString &type, const QString &name, const QString &address)
{
    close();
    DBtype()=type;
    DBname()=name;
    DBaddress()=address;
    dataBase() = QSqlDatabase::addDatabase(DBtype(),DBaddress()+DBname());
    return connect();
}

//Connection::Connection(Connection& c):
//    _db_type(c.DBtype()),
//    _db_name(c.DBname()),
//    _db_address(c.DBaddress()),
//    _data_base(c.dataBase()),
//    _connected(c.connected())
//{}

bool Connection::connect()
{
    if(connected())
        return connected();
    if(!_db_address.contains("http") && !QFile::exists(_db_address+_db_name))
        throw ConnectionError("The database does not exist!");
    return _connected=dataBase().open();
}

void Connection::close()
{
    dataBase().close();
    _connected=false;
}

std::pair<bool, QSqlQuery> Connection::execute(const QString& sql)
{
    if(connected() || connect())
    {
//        qDebug()<< "Trying execute SQL: " <<sql<<endl;
        QSqlQuery q;
        return std::make_pair(q.exec(sql), q);
    }
    else
        throw ConnectionError("Cannot connect to data base");
}

Connection::ConnectionError::ConnectionError(const QString & reason): _reason(reason)
{}
