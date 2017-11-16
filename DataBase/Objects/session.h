#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <ostream>
using namespace std;

class Session
{
public:
    Session(const quint64 signature=0,
            const quint64 auth_time=0,
            const quint64 user_upid=0,
            const quint64 valid_time=0);
    const quint64 signature() {return _signature;}
    const quint64 authTime() {return _auth_time;}
    const quint64 userUpid() {return _user_upid;}
    const quint64 validTime() {return _valid_time;}

    const quint64 authTime(const quint64);
    const quint64 userUpid(const quint64);
    const quint64 renewValidTime(const quint64);
private:
    quint64 _signature;
    quint64 _auth_time;
    quint64 _user_upid;
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

