#ifndef MAKEPAYMENTPACKET_H
#define MAKEPAYMENTPACKET_H

#include "../Packet.h"

class  MakePaymentPacket : public Packet
{
private:
    //fields
    quint64 _token;
    quint32 _machineId;
    quint64 _from;
    qint64 _to;
    qint64 _amount;
    quint64 _periodicity;
    QString _comment;
    QString _technicalComment;
    //method configuration
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    virtual PacketHolder specificHandle() const;
public:
     MakePaymentPacket();
     ~MakePaymentPacket();

     //selector-modifiers
     quint64& token()
     {
         return _token;
     }

     quint32& machineId()
     {
         return _machineId;
     }

     quint64& from()
     {
        return _from;
     }

     qint64& to()
     {
         return _to;
     }

     qint64& amount()
     {
         return _amount;
     }

     quint64& periodicity()
     {
         return _periodicity;
     }

     QString& comment()
     {
         return _comment;
     }

     QString& technicalComment()
     {
         return _technicalComment;
     }

     //selectors
     quint64 token() const
     {
         return _token;
     }

     quint32 machineId() const
     {
         return _machineId;
     }

     quint64 from() const
     {
        return _from;
     }

     qint64 to() const
     {
         return _to;
     }

     qint64 amount() const
     {
         return _amount;
     }

     quint64 periodicity() const
     {
         return _periodicity;
     }

     const QString& comment() const
     {
         return _comment;
     }

     const QString& technicalComment() const
     {
         return _technicalComment;
     }
};

#endif // MAKEPAYMENTPACKET_H
