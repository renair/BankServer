#include "session.h"

Session::Session(quint64 signature,
                 quint64 auth_time,
                 quint64 user_upid,
                 quint32 valid_time):
    _signature(signature),
    _auth_time(auth_time),
    _user_upid(user_upid),
    _valid_time(valid_time)
{

}
