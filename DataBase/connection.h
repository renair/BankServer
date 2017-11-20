#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class Connection
{
public:
//    Connection(Connection&);
    inline static Connection& getConnection(){return _connection;}
    ~Connection();
    std::pair<bool, QSqlQuery> execute(const QString&);
    const QString& DBtype() const{return _db_type;}
    const QString& DBname() const{return _db_name;}
    const QString& DBaddress() const{return _db_address;}
    bool reconnect(const QString& type,
                   const QString& name,
                   const QString& address);
    bool connected(){return _connected;}
    bool rollback();
private:
    QString _db_type;
    QString _db_name;
    QString _db_address;
    QSqlDatabase _data_base;
    bool _connected;
    static Connection _connection;

    Connection(const QString& type="QSQLITE",
               const QString& name="database.db",
               const QString& address= "../BankServer/");
    bool connect();
    void close();
    QString& DBtype(){return _db_type;}
    QString& DBname(){return _db_name;}
    QString& DBaddress(){return _db_address;}
    QSqlDatabase& dataBase(){return _data_base;}
//    bool& connected(){return _connected;}

public:
    class ConnectionError
    {
    public:
        ConnectionError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;
    };
};

#endif // CONNECTION_H
