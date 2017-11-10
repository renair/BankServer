#include "transfer.h"
#include <QDateTime>

Transfer::Transfer(const int id,
                   const int payer_id,
                   const int receiver_id,
                   const long time,
                   const QString& tech_comment,
                   const QString& comment,
                   const int period):
  _id(id),
  _account_payer_id(payer_id),
  _account_receiver_id(receiver_id),
  _time(time),
  _technical_comment(tech_comment),
  _comment(comment),
  _periodicity(period)
{}

Transfer::Transfer(const int payer_id,
                   const int receiver_id,
                   const long time,
                   const QString& tech_comment,
                   const QString& comment,
                   const int period):
    Transfer(-1,payer_id,receiver_id,time,tech_comment,comment,period)
{}

Transfer::Transfer(const Transfer& src):
    _id(src.id()),
    _account_payer_id(src.payerId()),
    _account_receiver_id(src.receiverId()),
    _time(src.time()),
    _technical_comment(src.techComment()),
    _comment(src.comment()),
    _periodicity(src.period())
{}

//Selectors
const int& Transfer::id() const
{
    return _id;
}
const int& Transfer::payerId() const
{
    return _account_payer_id;
}
const int& Transfer::receiverId() const
{
    return _account_receiver_id;
}
const int& Transfer::period() const
{
    return _periodicity;
}
const long& Transfer::time() const
{
    return _time;
}
const QString& Transfer::techComment() const
{
    return _technical_comment;
}
const QString& Transfer::comment() const
{
    return _comment;
}

//Selector-modifiers
int& Transfer::payerId()
{
    return _account_payer_id;
}
int& Transfer::receiverId()
{
    return _account_receiver_id;
}
int& Transfer::period()
{
    return _periodicity;
}
long& Transfer::time()
{
    return _time;
}
QString& Transfer::techComment()
{
    return _technical_comment;
}
QString& Transfer::comment()
{
    return _comment;
}

ostream& operator<<(ostream& os, const Transfer& t)
{
    QDateTime time;
    time.setTime_t(t.time());
    //SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, "rus");
    return os<< "Transfer" <<endl<< "{" <<endl
             << " ID: " << t.id() <<endl
             << " Payer ID: " << t.payerId() <<endl
             << " Receiver ID: " << t.receiverId() <<endl
             << " Time: " << time.toString().toStdString() <<endl
             << " Period: " << t.period() << "seconds" <<endl
             << " Technical comment: \"" << t.techComment().toUtf8().constData() << "\"" <<endl
             << " Comment: \"" << t.comment().toUtf8().constData() << "\"" <<endl<< "}" <<endl;
}
