#ifndef ATM_TABLE_H
#define ATM_TABLE_H

#include "DataBase/connection.h"
#include "DataBase/Objects/atm.h"

class ATMTable
{
public:
    ATMTable();
    ~ATMTable();
    bool createNew(const ATM&);
    bool update(const ATM&);
    ATM getById(const quint64);
private:
    Connection& _connection;

    ATMTable& operator=(const ATMTable&);

public:
    class ATMTableError
    {
    public:
        ATMTableError(const QString&);
        const QString& reason() {return _reason;}
    private:
        QString _reason;

        ATMTableError();
    };
};

#endif // ATM_TABLE_H
