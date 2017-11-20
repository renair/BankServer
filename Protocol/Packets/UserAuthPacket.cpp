#include "ErrorPacket.h"
#include "UserAuthPacket.h"
#include "DataBase/Objects/account.h"
#include "DataBase/Objects/user.h"
//#include "DataBase/Objects/session.h"
#include "DataBase/Access/account_table.h"
#include "DataBase/Access/user_table.h"
#include "DataBase/Access/session_table.h"

const char UserAuthPacket::_ID = 1;

UserAuthPacket::UserAuthPacket():
    _cardNumber(0),
    _password("")
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

QString& UserAuthPacket::password()
{
    return _password;
}

long long UserAuthPacket::card() const
{
    return _cardNumber;
}

const QString& UserAuthPacket::password() const
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
    data.append(_password);
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_cardNumber, sizeof(_cardNumber));
    char* pass = new char[buff.bytesAvailable()];
    buff.read(pass, buff.bytesAvailable());
    _password = QString(pass);
    delete pass;
}

PacketHolder UserAuthPacket::specificHandle() const
{
//    if(SessionTable().)
    return PacketHolder(clone());
}
