#include "Payment.h"

//NonVirtualInterface implementation
//do not use inline functions on case of we need to do something before or after payment
bool Payment::perform()
{
    return specificPerform();
}
