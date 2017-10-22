#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>

class Connection
{
public:
    Connection(QString type="QSQLITE", QString name="database.db", QString address="");
    ~Connection();
    bool open();
private:
    QString _dbType;
    QString _dbName;
    QString _dbAddress;

    Connection(Connection&);
    QString type(){return _dbType;}
    QString name(){return _dbName;}
    QString address(){return _dbAddress;}
};

#endif // CONNECTION_H
