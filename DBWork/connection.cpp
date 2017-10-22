#include <QSqlDatabase>
#include "DBWork/connection.h"

Connection::Connection(QString type, QString name, QString address):
    _dbType(type),
    _dbName(name),
    _dbAddress(address)
{}

Connection::~Connection()
{
    return;
}

bool Connection::open()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(type());
    db.setDatabaseName(address()+name());
    return db.open();
}
