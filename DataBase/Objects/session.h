#ifndef SESSION_H
#define SESSION_H

#include <QString>

class Session
{
public:
    Session(const quint64 signature=0,
            const quint64 auth_time=0,
            const quint64 user_upid=0,
            const quint32 valid_time=0);
//    Session(const qint64 signature,
//            const qint64 auth_time,
//            const qint64 user_upid,
//            const qint64 valid_time);
    const quint64 signature() const {return _signature;}
    const quint64 authTime() const {return _auth_time;}
    const quint64 userUpid() const {return _user_upid;}
    const quint32 validTime() const {return _valid_time;}

    const quint64 authTime(const quint64);
    const quint64 userUpid(const quint64);
    const quint32 renewValidTime(const quint32);
private:
    quint64 _signature;
    quint64 _auth_time;
    quint64 _user_upid;
    quint32 _valid_time;
};

#endif // SESSION_H

