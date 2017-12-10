#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <ostream>
using namespace std;

class Session
{
    friend class SessionTable;
public:
    Session(const quint64 signature,
            const quint64 auth_time,
            const quint64 user_upid,
            const quint64 card_id,
            const quint64 atm_id,
            const quint64 valid_time);
    Session(const quint64 auth_time=0,
            const quint64 user_upid=0,
            const quint64 card_id=0,
            const quint64 atm_id=0,
            const quint64 valid_time=0);

    quint64 signature() const {return _signature;}
    quint64 authTime() const {return _auth_time;}
    quint64 userUpid() const {return _user_upid;}
    quint64 cardId() const {return _card_id;}
    quint64 atmId() const {return _atm_id;}
    quint64 validTime() const {return _valid_time;}

    quint64 authTime(quint64);
    quint64 userUpid(quint64);
    quint64 cardId(quint64);
    quint64 atmId(quint64);
    quint64 renewValidTime(quint64);
private:
    quint64 _signature;
    quint64 _auth_time;
    quint64 _user_upid;
    quint64 _card_id;
    quint64 _atm_id;
    quint64 _valid_time;

public:
    class SessionError
    {
    public:
        SessionError(const QString&);
        const QString& reason() const {return _reason;}
    private:
        QString _reason;
        SessionError();
    };
};

ostream& operator <<(ostream&, const Session&);

#endif // SESSION_H

