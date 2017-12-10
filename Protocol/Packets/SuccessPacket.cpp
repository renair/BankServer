#include "SuccessPacket.h"

using namespace std;

SuccessPacket::SuccessPacket(const std::string& msg):
    _message(msg)
{}

SuccessPacket::~SuccessPacket()
{}

char SuccessPacket::specificGetID() const
{
    return 7;
}

PacketHolder SuccessPacket::specificClone() const
{
    return PacketHolder(new SuccessPacket(*this));
}

QByteArray SuccessPacket::specificDump() const
{
    QByteArray res;
    res.append(_message.data(), _message.size()+1);
    return res;
}

void SuccessPacket::specificLoad(QBuffer& buf)
{
    QByteArray data = buf.readAll();
    _message = data.data();
}
