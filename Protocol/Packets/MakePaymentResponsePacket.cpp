#include "MakePaymentResponsePacket.h"


MakePaymentResponsePacket::MakePaymentResponsePacket()
{}

MakePaymentResponsePacket::~MakePaymentResponsePacket()
{}

char MakePaymentResponsePacket::specificGetID() const
{
    return -4;
}

PacketHolder MakePaymentResponsePacket::specificClone() const
{
    return PacketHolder(new MakePaymentResponsePacket(*this));
}

QByteArray MakePaymentResponsePacket::specificDump() const
{
    return QByteArray(1, _paymentStatus);
}

void MakePaymentResponsePacket::specificLoad(QBuffer& data)
{
    data.getChar(&_paymentStatus);
}

MakePaymentResponsePacket::PaymentStatus MakePaymentResponsePacket::getStatusFromId(char id)
{
    switch (id) {
    case 1:
        return PAYMENT_SUCCESSFULL;
    case 2:
        return NOT_ENOUGH_MONEY;
    case 3:
        return SERVER_ERROR;
    default:
        return UNKNOWN_ERROR;
    }
}

void MakePaymentResponsePacket::setPaymentStatus(PaymentStatus status)
{
    _paymentStatus = status;
}

MakePaymentResponsePacket::PaymentStatus MakePaymentResponsePacket::getPaymentStatus() const
{
    return getStatusFromId(_paymentStatus);
}
