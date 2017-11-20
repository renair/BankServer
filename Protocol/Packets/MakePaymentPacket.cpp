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
    data.append((char*)&_from, sizeof(_from));
    data.append((char*)&_to, sizeof(_to));
    data.append((char*)&_amount, sizeof(_amount));
    data.append(_comment.toStdString().c_str(), _comment.toStdString().length());
    return data;
}

void MakePaymentPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_from, sizeof(_from));
    data.read((char*)&_to, sizeof(_to));
    data.read((char*)&_amount, sizeof(_amount));
    _comment = QString(data.readAll());
}

PacketHolder MakePaymentPacket::specificHandle() const
{
    if(!SessionTable().renewSession(token()))
        return PacketHolder(new ErrorPacket("You are not authorized"));
    Account payer;
    Account recipient;
    Transfer transfer;
    quint64 time = QDateTime::currentDateTime().toTime_t();
    try
    {
        payer = AccountTable().getById(from());
        recipient = AccountTable().getById(to());
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
        AccountTable().update(payer);
        AccountTable().update(recipient);
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
    MakePaymentResponsePacket* result = new MakePaymentResponsePacket();
    result->setPaymentStatus(MakePaymentResponsePacket::PaymentStatus::PAYMENT_SUCCESSFULL);
    return PacketHolder(result);
}
