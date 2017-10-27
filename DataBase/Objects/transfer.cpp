#include "transfer.h"

Transfer::Transfer(int id,
                   int payer_id,
                   int receiver_id,
                   QString tech_comment,
                   QString comment,
                   int period):
  _id(id),
  _account_payer_id(payer_id),
  _account_receiver_id(receiver_id),
  _technical_comment(tech_comment),
  _comment(comment),
  _periodicity(period)
{
    qDebug("New money widthraw");
}

Transfer::Transfer(int payer_id,
                   int receiver_id,
                   QString tech_comment,
                   QString comment,
                   int period):
    Transfer(-1,payer_id,receiver_id,tech_comment,comment,period)
{}

Transfer::Transfer(Transfer& src):
    _id(src.id()),
    _account_payer_id(src.payer_id()),
    _account_receiver_id(src.receiver_id()),
    _technical_comment(src.tech_comment()),
    _comment(src.comment()),
    _periodicity(src.period())
{}

bool Transfer::specificPerform()
{
    qDebug("Make money transaction!!!");
    return true;
}

//Selectors
Transfer::id() const
{
    return _id;
}
Transfer::payer_id() const
{
    return _account_payer_id;
}
Transfer::receiver_id() const
{
    return _account_receiver_id;
}
Transfer::period() const
{
    return _periodicity;
}
const QString Transfer::tech_comment() const
{
    return _technical_comment;
}
const QString Transfer::comment() const
{
    return _comment;
}

//Modifiers
void Transfer::payer_id(int i)
{
    _account_payer_id=i;
}
void Transfer::receiver_id(int i)
{
    _account_receiver_id=i;
}
void Transfer::period(int i)
{
    _periodicity=i;
}
void Transfer::tech_comment(const QString& s)
{
    _technical_comment=s;
}
void Transfer::comment(const QString& s)
{
    _comment=s;
}

ostream& operator<<(ostream& os, const Transfer& t)
{
    return os<< "Transfer ID: " << t.id() <<endl
             << "Payer ID: " << t.payer_id() <<endl
             << "Receiver ID: " << t.receiver_id() <<endl
             << "Period: " << t.period() << "seconds" <<endl
             << "Technical comment: \"" << t.tech_comment().toUtf8().constData() << "\"" <<endl
             << "Comment: \"" << t.comment().toUtf8().constData() << "\"" <<endl;
}
