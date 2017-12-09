#include <QDateTime>
#include "session.h"

#include <QDebug>

Session::Session(quint64 signature,
                 quint64 auth_time,
                 quint64 user_upid,
                 quint64 card_id,
                 quint64 atm_id,
                 quint64 valid_time):
    _signature(signature),
    _auth_time(auth_time),
    _user_upid(user_upid),
    _card_id(card_id),
    _atm_id(atm_id),
    _valid_time(valid_time)
{}

Session::Session(const quint64 auth_time,
                 const quint64 user_upid,
                 const quint64 card_id,
                 const quint64 atm_id,
                 const quint64 valid_time):
    Session(0,auth_time,user_upid,card_id, atm_id, valid_time)
{}

quint64 Session::authTime(quint64 time)
{
    if(authTime())
        throw SessionError("Cannot change auth time");
    return _auth_time=time;
}

quint64 Session::userUpid(quint64 user)
{
    if(userUpid())
        throw SessionError("Cannot change user");
    return _user_upid=user;
}

quint64 Session::cardId(quint64 card)
{
    if(cardId())
        throw SessionError("Cannot change card");
    return _card_id=card;
}

quint64 Session::atmId(quint64 atm)
{
    if(atmId())
        throw SessionError("Cannot change atm");
    return _atm_id=atm;
}

quint64 Session::renewValidTime(quint64 time)
{
    if(validTime()==0 || time<validTime())
        throw SessionError("Cannot change valid time");
    if(time<authTime())
        throw SessionError("Valid time cannot be less than auth time");
    return _valid_time=time;
}

ostream& operator <<(ostream& os, const Session& s)
{
    QDateTime a_time;
    a_time.setTime_t(s.authTime());
    QDateTime v_time;
    v_time.setTime_t(s.validTime());
    return os<< "Session" <<endl<< "{" <<endl
             << " Signature: " << s.signature() <<endl
             << " User: " << s.userUpid() <<endl
             << " By card: " << s.cardId() <<endl
             << " On: " << s.atmId() <<endl
             << " Auth time: " << a_time.toString().toStdString() <<endl
             << " Valid time: " << v_time.toString().toStdString() <<endl<< "}" <<endl;
}

Session::SessionError::SessionError(const QString & reason): _reason(reason)
{}
