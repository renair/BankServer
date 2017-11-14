#include "withdraw.h"

Withdraw::Withdraw(const quint64 id,
                   const quint64 payer_id,
                   const quint64 atm_id,
                   const quint64 time,
                   const QString& tech_comment,
                   const QString& comment):
    _id(id),
    _account_payer_id(payer_id),
    _atm_id(atm_id),
    _time(time),
    _technical_comment(tech_comment),
    _comment(comment)
{}

Withdraw::Withdraw(const quint64 payer_id,
                   const quint64 atm_id,
                   const quint64 time,
                   const QString &tech_comment,
                   const QString &comment):
    Withdraw(0,payer_id,atm_id,time,tech_comment,comment)
{}

Withdraw::~Withdraw(){}

Withdraw::Withdraw(const Withdraw &src):
    _id(src.id()),
    _account_payer_id(src.payerId()),
    _atm_id(src.atmId()),
    _time(src.time()),
    _technical_comment(src.techComment()),
    _comment(src.comment())
{}
