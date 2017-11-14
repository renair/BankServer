#ifndef TRANSFER_H
#define TRANSFER_H

#include <QString>
#include <ostream>
using namespace std;

#include "payment.h"

class Transfer
{
public:
    explicit Transfer(const quint64 id,
                      const quint64 payer_id,
                      const quint64 receiver_id,
                      const quint64 time,
                      const QString& tech_comment,
                      const QString& comment="",
                      const quint32 period=0);
    Transfer(const quint64 payer_id=0,
             const quint64 receiver_id=0,
             const quint64 time=0,
             const QString& tech_comment="transfer",
             const QString& comment="",
             const quint32 period=0);
    ~Transfer(){}
    Transfer(const Transfer&);
    //Selectors
    const quint64& id() const       {return _id;}
    const quint64& payerId() const  {return _account_payer_id;}
    const quint64& receiverId()const{return _account_receiver_id;}
    const quint32& period() const   {return _periodicity;}
    const quint64& time() const    {return _time;}
    const QString& techComment()const{return _technical_comment;}
    const QString& comment()const{return _comment;}
    //Selector-modifiers
    quint64& payerId()          {return _account_payer_id;}
    quint64& receiverId()       {return _account_receiver_id;}
    quint32& period()           {return _periodicity;}
    quint64& time()            {return _time;}
    QString& techComment()  {return _technical_comment;}
    QString& comment()      {return _comment;}
private:
    quint64 _id;
    quint64 _account_payer_id;
    quint64 _account_receiver_id;
    quint64 _time;
    QString _technical_comment;
    QString _comment;
    quint32 _periodicity;

    bool specificPerform();
    bool specificIsPeriodic();
    Payment* specificNextPayment();
};

ostream& operator<<(ostream&, const Transfer&);

#endif // TRANSFER_H
