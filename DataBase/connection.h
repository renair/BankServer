#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class Connection
{
public:
    Connection(QString type="QSQLITE", QString name="database.db", QString address= "../BankServer/");
    ~Connection();
    Connection(Connection&);
    std::pair<bool, QSqlQuery> execute(const QString&);
    bool connect();
    const QString& DBtype(){return _db_type;}
    const QString& DBname(){return _db_name;}
    const QString& DBaddress(){return _db_address;}
    const bool& connected() const{return _connected;}
private:
    QString _db_type;
    QString _db_name;
    QString _db_address;
    QSqlDatabase _data_base;
    bool _connected;

    const QSqlDatabase& dataBase(){return _data_base;}
    bool& connected(){return _connected;}
};

#endif // CONNECTION_H
