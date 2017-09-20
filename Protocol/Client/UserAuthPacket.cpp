#include "UserAuthPacket.h"

using namespace Protocol;

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

char UserAuthPacket::getID() const
{
    return _ID;
}

Packet* UserAuthPacket::clone() const
{
    return new UserAuthPacket(*this);
}

QByteArray UserAuthPacket::dump() const
{
    QByteArray arr;
    QBuffer buff(&arr);
    buff.open(QBuffer::WriteOnly);
    buff.write(&_ID, sizeof(_ID));
    buff.write((char*)&_cardnum, sizeof(_cardnum));
    buff.write((char*)&_password, sizeof(_password));
    return arr;
}

void UserAuthPacket::load(QByteArray& bytes)
{
    QBuffer buff(&bytes);
    buff.open(QBuffer::ReadOnly);
    char i = 0;
    buff.read(&i, sizeof(i));
    if(i != getID())
    {
        //throw some error
    }
    buff.read((char*)&_cardnum, sizeof(_cardnum));
    buff.read((char*)&_password, sizeof(_password));
}

void UserAuthPacket::handle() const
{
    //do some stuff here
}
