#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QString>
#include <ostream>
using namespace std;

class Withdraw
{
public:
    Withdraw(quint64 id,
             quint64 payer_id,
             quint64 atm_id,
             quint32 amount,
             quint64 time,
             const QString& tech_comment,
             const QString& comment="");
    explicit Withdraw(quint64 payer_id=0,
                      quint64 atm_id=0,
                      quint32 amount=0,
                      quint64 time=0,
                      const QString& tech_comment="withdraw",
                      const QString& comment="");
    ~Withdraw();
    Withdraw(const Withdraw&);
    //Selectors
    const quint64& id() const       {return _id;}
    const quint64& payerId() const {return _account_payer_id;}
    const quint64& atmId() const   {return _atm_id;}
    quint64 amount() const {return _amount;}
    const quint64& time() const    {return _time;}
    const QString& techComment()const {return _technical_comment;}
    const QString& comment()     const {return _comment;}
    //Selector-modifiers
    quint64& payerId(){return _account_payer_id;}
    quint64& atmId(){return _atm_id;}
    quint64& amount() {return _amount;}
    quint64& time(){return _time;}
    QString& techComment(){return _technical_comment;}
    QString& comment(){return _comment;}
private:
    quint64& id();
    quint64 _id;
    quint64 _account_payer_id;
    quint64 _atm_id;
    quint64 _amount;
    quint64 _time;
    QString _technical_comment;
    QString _comment;
public:
    class WithdrawError
    {
    public:
        WithdrawError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;
        WithdrawError();
    };
};

#endif // WITHDRAW_H
