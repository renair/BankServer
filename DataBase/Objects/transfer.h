#ifndef TRANSFER_H
#define TRANSFER_H

#include <QString>
#include <ostream>
using namespace std;

#include "payment.h"

class Transfer
{
public:
    explicit Transfer(const int id,
                      const int payer_id,
                      const int receiver_id,
                      const long time,
                      const QString& tech_comment,
                      const QString& comment="",
                      const int period=0);
    Transfer(const int payer_id=-1,
             const int receiver_id=-1,
             const long time=0,
             const QString& tech_comment="transfer",
             const QString& comment="",
             const int period=0);
    ~Transfer(){}
    Transfer(const Transfer&);
    //Selectors
    const int& id() const;
    const int& payerId() const;
    const int& receiverId() const;
    const int& period() const;
    const long& time() const;
    const QString& techComment() const;
    const QString& comment() const;
    //Selector-modifiers
    int& payerId();
    int& receiverId();
    int& period();
    long& time();
    QString& techComment();
    QString& comment();
private:
    int& id();
    //Identifier, not initialized(NI): -1
    int _id;
    //The account from which transfer will be made, NI: -1
    int _account_payer_id;
    //The account is where the transfer will be made, NI: -1
    int _account_receiver_id;
    //Number of seconds after start of Unix age
    long _time;
    /*The comment need for specific transfers,
        as the transfer to the account of the mobile operator
        indicating the phone number*/
    QString _technical_comment;
    //The comment that was left by the user
    QString _comment;
    //The frequency with which the transfer will be made (in seconds), NI: 0
    int _periodicity;

    bool specificPerform();
};

ostream& operator<<(ostream&, const Transfer&);

#endif // TRANSFER_H
