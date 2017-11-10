#include "UserAuthPacket.h"

const char UserAuthPacket::_ID = 1;

UserAuthPacket::UserAuthPacket():
    _cardnum(0),
    _password(0)
{}

UserAuthPacket::UserAuthPacket(long long card, short pass):
    _cardnum(card),
    _password(pass)
{}

UserAuthPacket::UserAuthPacket(const UserAuthPacket& pack):
    _cardnum(pack._cardnum),
    _password(pack._password)
{}

long long& UserAuthPacket::card()
{
    return _cardnum;
}

short& UserAuthPacket::password()
{
    return _password;
}

long long UserAuthPacket::card() const
{
    return _cardnum;
}

short UserAuthPacket::password() const
{
    return _password;
}

char UserAuthPacket::specificGetID() const
{
    return _ID;
}

PacketHolder UserAuthPacket::specificClone() const
{
    return PacketHolder(new UserAuthPacket(*this));
}

QByteArray UserAuthPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_cardnum, sizeof(_cardnum));
    data.append((char*)&_password, sizeof(_password));
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_cardnum, sizeof(_cardnum));
    buff.read((char*)&_password, sizeof(_password));
}