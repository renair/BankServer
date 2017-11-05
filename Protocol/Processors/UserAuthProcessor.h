#ifndef USERAUTHPROCESSOR_H
#define USERAUTHPROCESSOR_H

#include "../PacketProcessor.h"

class UserAuthProcessor : public PacketProcessor
{
private:
    virtual Packet* specificPerform(Packet*);
public:
    UserAuthProcessor(); //reqire ClientService
    ~UserAuthProcessor();
};

#endif // USERAUTHPROCESSOR_H
