#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <ostream>
using namespace std;

class Account
{
    friend class AccountTable;
public:
    Account(quint64 id=0,
            quint64 owner=0,
            int type=0,
            const QString& pin="",
            quint32 money=0);

    const quint64& id() const {return _id;}
    const quint64& owner() const {return _owner;}
    const int& type() const {return _type;}
    const quint32& moneyAmount() const {return _money_amount;}

    quint32 moneyAdd(qint32);
    quint32 moneyDivide(qint32);
    bool checkPin(const QString&);
    bool setNewPin(const QString& new_pin, const QString& old_pin="");
private:
    quint64 _id;
    quint64 _owner;
    int _type;
    QString _pin;
    quint32 _money_amount;

    const QString& pin() const {return _pin;}

public:
    class AccountError
    {
    public:
        AccountError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;
    };
};

ostream& operator<<(ostream&, const Account&);

#endif // ACCOUNT_H
