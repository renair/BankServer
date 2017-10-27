#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QString>
#include <ostream>
using namespace std;
#include "payment.h"

class Withdraw : public Payment
{
public:
    explicit Withdraw(const int id,
                      const int payer_id,
                      const int atm_id,
                      const long time,
                      const QString& tech_comment,
                      const QString& comment="");
    Withdraw(const int payer_id=-1,
             const int atm_id=-1,
             const long time=0,
             const QString& tech_comment="withdraw",
             const QString& comment="");
    ~Withdraw();
    Withdraw(const Withdraw&);
    //Selectors
    const int& id() const;
    const int& payer_id() const;
    const int& atm_id() const;
    const long& time() const;
    const QString& tech_comment() const;
    const QString& comment() const;
    //Selector-modifiers
    int& payer_id();
    int& atm_id();
    long& time();
    QString& tech_comment();
    QString& comment();
private:
    int& id();
    //Identifier, not initialized(NI): -1
    int _id;
    //The account from which transfer will be made, NI: -1
    int _account_payer_id;
    //The account is where the transfer will be made, NI: -1
    int _atm_id;
    //Number of seconds after start of Unix age
    long _time;
    /*The comment in which */
    QString _technical_comment;
    //The comment that was left by the user
    QString _comment;
};

#endif // WITHDRAW_H
