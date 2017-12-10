#include "CancelPeriodicPaymentPacket.h"
#include "ErrorPacket.h"
#include "SuccessPacket.h"

CancelPeriodicPaymentPacket::CancelPeriodicPaymentPacket(quint64 t, quint64 mi, quint64 pi):
    _token(t),
    _machineId(mi),
    _paymentId(pi)
{}

CancelPeriodicPaymentPacket::~CancelPeriodicPaymentPacket()
{}

char CancelPeriodicPaymentPacket::specificGetID() const
{
    return 8;
}

PacketHolder CancelPeriodicPaymentPacket::specificClone() const
{
    return PacketHolder(new CancelPeriodicPaymentPacket(*this));
}

void CancelPeriodicPaymentPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)_token, sizeof(_token));
    buff.read((char*)_machineId, sizeof(_machineId));
    buff.read((char*)_paymentId, sizeof(_paymentId));
}

QByteArray CancelPeriodicPaymentPacket::specificDump() const
{
    QByteArray res;
    res.append((char*)_token, sizeof(_token));
    res.append((char*)_machineId, sizeof(_machineId));
    res.append((char*)_paymentId, sizeof(_paymentId));
    return res;
}

PacketHolder CancelPeriodicPaymentPacket::specificHandle() const
{
    //TODO implement packet
    return PacketHolder(new ErrorPacket("This method is not available now."));
}
