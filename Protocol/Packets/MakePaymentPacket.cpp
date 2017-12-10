#include <QDateTime>
#include "DataBase/Access/session_table.h"
#include "MakePaymentPacket.h"
#include "MakePaymentResponsePacket.h"
#include "ErrorPacket.h"
#include "DataBase/Access/session_table.h"
#include "DataBase/Access/account_table.h"
#include "DataBase/Access/atm_table.h"
#include "DataBase/Access/transfer_table.h"
#include "DataBase/Access/withdraw_table.h"
#include "DataBase/Objects/account.h"
#include "DataBase/Objects/atm.h"
#include "DataBase/Objects/transfer.h"
#include "DataBase/Objects/withdraw.h"
#include "DataBase/Objects/atm.h"

MakePaymentPacket::MakePaymentPacket()
{}

MakePaymentPacket::~MakePaymentPacket()
{}

char MakePaymentPacket::specificGetID() const
{
    return 4;
}

PacketHolder MakePaymentPacket::specificClone() const
{
    return PacketHolder(new MakePaymentPacket(*this));
}

QByteArray MakePaymentPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_machineId, sizeof(_machineId));
    data.append((char*)&_from, sizeof(_from));
    data.append((char*)&_to, sizeof(_to));
    data.append((char*)&_amount, sizeof(_amount));
    std::string str = _comment.toStdString();
    data.append(str.c_str(), str.length()+1);
    return data;
}

void MakePaymentPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_machineId, sizeof(_machineId));
    data.read((char*)&_from, sizeof(_from));
    data.read((char*)&_to, sizeof(_to));
    data.read((char*)&_amount, sizeof(_amount));
    _comment = QString(data.readAll());
}

PacketHolder MakePaymentPacket::specificHandle() const
{
    if(!SessionTable().renewSession(token()))
    {
        return PacketHolder(new ErrorPacket("You are not authorized"));
    }
    AccountTable accountTable;
    quint64 time = QDateTime::currentDateTime().toTime_t();
    if(to()<0)
    {
        Account payer;
        ATM atm;
        Withdraw withdraw;
        try
        {
            payer = accountTable.getById(from());
            atm = ATMTable().getById(to()*(-1));
            payer.moneyDivide(amount());
            withdraw = Withdraw(from(),
                                to()*(-1),
                                amount(),
                                time,
                                "withdraw",
                                comment());
            WithdrawTable().createNew(withdraw);
            accountTable.update(payer);
        }
        catch(const Account::AccountError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
        catch(const Withdraw::WithdrawError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
        catch(const AccountTable::AccountTableError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
        catch(const WithdrawTable::WithdrawTableError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
    }
    else
    {
        Account payer;
        Account recipient;
        Transfer transfer;
        try
        {
            payer = accountTable.getById(from());
            recipient = accountTable.getById(to());
            payer.moneyDivide(amount());
            recipient.moneyAdd(amount());
            transfer = Transfer(from(),
                                to(),
                                amount(),
                                time,
                                "transfer",
                                comment(),
                                0);
            TransferTable().createNew(transfer);
            accountTable.update(payer);
            accountTable.update(recipient);
        }
        catch(const Account::AccountError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
        catch(const Transfer::TransferError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
        catch(const AccountTable::AccountTableError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
        catch(const TransferTable::TransferTableError& error)
        {
            return PacketHolder(new ErrorPacket(error.reason()));
        }
    }
    MakePaymentResponsePacket* result = new MakePaymentResponsePacket();
    result->setPaymentStatus(MakePaymentResponsePacket::PaymentStatus::PAYMENT_SUCCESSFULL);
    return PacketHolder(result);
}
