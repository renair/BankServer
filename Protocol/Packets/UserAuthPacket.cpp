#include "UserAuthPacket.h"

const char UserAuthPacket::_ID = 1;

UserAuthPacket::UserAuthPacket():
    _cardNumber(0),
    _password(0)
{}

UserAuthPacket::UserAuthPacket(long long card, short pass):
    _cardNumber(card),
    _password(pass)
{}

UserAuthPacket::UserAuthPacket(const UserAuthPacket& pack):
    _cardNumber(pack._cardNumber),
    _password(pack._password)
{}

long long& UserAuthPacket::card()
{
    return _cardNumber;
}

short& UserAuthPacket::password()
{
    return _password;
}

long long UserAuthPacket::card() const
{
    return _cardNumber;
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
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    data.append((char*)&_password, sizeof(_password));
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_cardNumber, sizeof(_cardNumber));
    buff.read((char*)&_password, sizeof(_password));
}

PacketHolder UserAuthPacket::specificHandle() const
{
    return PacketHolder(clone());
}
