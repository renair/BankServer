#include "session.h"

Session::Session(const quint64 signature,
                 const quint64 auth_time,
                 const quint64 user_upid,
                 const quint32 valid_time):
    _signature(signature),
    _auth_time(auth_time),
    _user_upid(user_upid),
    _valid_time(valid_time)
{

}
