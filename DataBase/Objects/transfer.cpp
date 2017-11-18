#include "transfer.h"
#include <QDateTime>

Transfer::Transfer(quint64 id,
                   quint64 payer_id,
                   quint64 receiver_id,
                   quint32 amount,
                   quint64 time,
                   const QString& tech_comment,
                   const QString& comment,
                   quint32 period):
  _id(id),
  _account_payer_id(payer_id),
  _account_receiver_id(receiver_id),
  _amount(amount),
  _time(time),
  _technical_comment(tech_comment),
  _comment(comment),
  _periodicity(period)
{}

Transfer::Transfer(quint64 payer_id,
                   quint64 receiver_id,
                   quint32 amount,
                   quint64 time,
                   const QString& tech_comment,
                   const QString& comment,
                   quint32 period):
    Transfer(-1,payer_id,receiver_id,amount,time,tech_comment,comment,period)
{}

Transfer::Transfer(const Transfer& src):
    _id(src.id()),
    _account_payer_id(src.payerId()),
    _account_receiver_id(src.receiverId()),
    _amount(src.amount()),
    _time(src.time()),
    _technical_comment(src.techComment()),
    _comment(src.comment()),
    _periodicity(src.period())
{}

ostream& operator<<(ostream& os, const Transfer& t)
{
    QDateTime time;
    time.setTime_t(t.time());
    return os<< "Transfer" <<endl<< "{" <<endl
             << " ID: " << t.id() <<endl
             << " Payer ID: " << t.payerId() <<endl
             << " Receiver ID: " << t.receiverId() <<endl
             << " Amount: " << t.amount() <<endl
             << " Time: " << time.toString().toStdString() <<endl
             << " Period: " << t.period() << "seconds" <<endl
             << " Technical comment: \"" << t.techComment().toUtf8().constData() << "\"" <<endl
             << " Comment: \"" << t.comment().toUtf8().constData() << "\"" <<endl<< "}" <<endl;
}
