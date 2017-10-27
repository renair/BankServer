#ifndef TRANSFER_H
#define TRANSFER_H

#include <QString>
#include <ostream>
using namespace std;

#include "payment.h"

class Transfer : public Payment
{
public:
    explicit Transfer(int id,
                      int payer_id,
                      int receiver_id,
                      QString tech_comment,
                      QString comment="",
                      int period=0);
    Transfer(int payer_id=-1,
             int receiver_id=-1,
             QString tech_comment="",
             QString comment="",
             int period=0);
    ~Transfer(){}
    Transfer(Transfer&);
    //Selectors
    id() const;
    payer_id() const;
    receiver_id() const;
    period() const;
    const QString tech_comment() const;
    const QString comment() const;
    //Modifiers
    void payer_id(int);
    void receiver_id(int);
    void period(int);
    void tech_comment(const QString&);
    void comment(const QString&);
private:
    int id(int);
    //Identifier, not initialized(NI): -1
    int _id;
    //The account from which transfer will be made, NI: -1
    int _account_payer_id;
    //The account is where the transfer will be made, NI: -1
    int _account_receiver_id;
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
