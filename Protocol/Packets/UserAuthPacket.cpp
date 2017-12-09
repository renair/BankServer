#include <QDateTime>
#include "ErrorPacket.h"
#include "UserAuthPacket.h"
#include "UserAuthResponsePacket.h"
#include "DataBase/Access/account_table.h"
#include "DataBase/Access/user_table.h"
#include "DataBase/Access/session_table.h"

const char UserAuthPacket::_ID = 1;

UserAuthPacket::UserAuthPacket():
    _cardNumber(0),
    _password("")
{}

UserAuthPacket::UserAuthPacket(long long card, const QString& pass):
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
    std::string str = _password.toStdString();
    data.append(str.c_str(), str.length()+1);
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_cardNumber, sizeof(_cardNumber));
    _password = QString(buff.readAll());
}

PacketHolder UserAuthPacket::specificHandle() const
{
    try
    {
        AccountTable accountTable;
        SessionTable sessionTable;
        Account account = accountTable.getById(card());
        quint64 owner = accountTable.getOwnerById(card());
        if(account.checkPin(password()))
        {
            pair<bool, quint64> bool_signature;
            bool_signature = sessionTable.isAuthorized(owner,card());
            if(bool_signature.first)
            {
                if(sessionTable.getBySignature(bool_signature.second).atmId()==0/*atm()*/
                        && sessionTable.renewSession(bool_signature.second))
                {
                    return PacketHolder(new UserAuthResponsePacket(bool_signature.second));
                }
                else
                {
                    return PacketHolder(new ErrorPacket("You are already authorized from another ATM."));
                }
            }
            else
            {
                quint64 auth_time = QDateTime::currentDateTime().toTime_t();
                //TODO
                Session session(auth_time, owner, card(), /*atm(),*/0, auth_time + 60*10); //ten minutes
                sessionTable.createNew(session);
                return PacketHolder(new UserAuthResponsePacket(session.signature()));
            }
        }
        else
        {
            return PacketHolder(new ErrorPacket("Incorrect password."));
        }
    }
    catch(const SessionTable::SessionTableError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const AccountTable::AccountTableError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const UserTable::UserTableError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const Connection::ConnectionError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const Account::AccountError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
    catch(const User::UserError& error)
    {
        return PacketHolder(new ErrorPacket(error.reason()));
    }
}
