#include "withdraw.h"

Withdraw::Withdraw(const int id,
                   const int payer_id,
                   const int atm_id,
                   const long time,
                   const QString& tech_comment,
                   const QString& comment):
    _id(id),
    _account_payer_id(payer_id),
    _atm_id(atm_id),
    _time(time),
    _technical_comment(tech_comment),
    _comment(comment)
{}

Withdraw::~Withdraw(){}

Withdraw::Withdraw(const Withdraw &src):
    _id(src.id()),
    _account_payer_id(src.payer_id()),
    _atm_id(src.atm_id()),
    _time(src.time()),
    _technical_comment(src.tech_comment()),
    _comment(src.comment())
{}

//Selectors
const int& Withdraw::id() const
{
    return _id;
}
const int& Withdraw::payer_id() const
{
    return _account_payer_id;
}
const int& Withdraw::atm_id() const
{
    return _atm_id;
}
const long& Withdraw::time() const
{
    return _time;
}
const QString& Withdraw::tech_comment() const
{
    return _technical_comment;
}
const QString& Withdraw::comment() const
{
    return _comment;
}
//Selector-modifiers
int& Withdraw::payer_id()
{
    return _account_payer_id;
}
int& Withdraw::atm_id()
{
    return _atm_id;
}
long& Withdraw::time()
{
    return _time;
}
QString& Withdraw::tech_comment()
{
    return _technical_comment;
}
QString& Withdraw::comment()
{
    return _comment;
}
