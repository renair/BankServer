#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <ostream>
using namespace std;

class Account
{
    friend class AccountTable;
public:
    Account(const quint64 id=0,
            const quint64 owner=0,
            const int type=0,
            const QString& pin="",
            const quint32 money=0);

    const quint64& id() const {return _id;}
    const quint64& owner() const {return _owner;}
    const int& type() const {return _type;}
    const quint32& money_amount() const {return _money_amount;}

    const quint32 money_add(const qint32);
    const quint32 money_divide(const qint32);
    bool checkPin(const QString&);
    bool setNewPin(const QString& new_pin, const QString& old_pin="");
private:
    quint64 _id;
    quint64 _owner;
    int _type;
    QString _pin;
    quint32 _money_amount;

    const QString& pin() const {return _pin;}
//    quint64& id();
//    quint64& owner();
//    int& type();
//    QString& pin();
//    quint32& money_amount();
//    Account(const qint64 id,
//            const qint64 owner,
//            const int type,
//            const QString& pin,
//            const qint64 money);

    class AccountError
    {
    public:
        AccountError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;
    };
};

#endif // ACCOUNT_H
