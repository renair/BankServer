#include <QDebug>
#include <QFileInfo>
#include "DataBase/connection.h"

Connection::Connection(QString type, QString name, QString address):
    _db_type(type),
    _db_name(name),
    _db_address(address),
    _data_base(),
    _connected(false)
{
    _data_base = QSqlDatabase::addDatabase(_db_type);
    _data_base.setDatabaseName(_db_address+_db_name);
    qDebug()<<"Connection constructor, _connected: " << _data_base.isOpen() <<endl;
}

Connection::~Connection()
{
    _data_base.close();
}

Connection::Connection(Connection& c):
    _db_type(c.DBtype()),
    _db_name(c.DBname()),
    _db_address(c.DBaddress()),
    _data_base(c.dataBase()),
    _connected(c.connected())
{}

bool Connection::connect()
{
    if(connected())
        return connected();
    if(!_db_address.contains("http") && !QFile::exists(_db_address+_db_name))
//        throw ConnectionError("The database does not exist!");
        return false;
    return connected()=_data_base.open();
}

std::pair<bool, QSqlQuery> Connection::execute(const QString& sql)
{
    if(!connected())
//        throw ConnectionError("Cannot connect to data base");
        throw QString("Cannot connect to data base");
    QSqlQuery q;
    return std::make_pair(q.exec(sql), q);
}
