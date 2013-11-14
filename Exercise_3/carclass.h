#ifndef CARCLASS_H
#define CARCLASS_H

#include "osapi/Thread.hpp"
#include "osapi/MsgQueue.hpp"
#include "types.h"
#include "entryclass.h"
#include "exitclass.h"


class CarClass : public osapi::ThreadFunctor
{
public:
    CarClass(EntryClass* entry, ExitClass* exit, unsigned int carID);
    void run();
private:
    void handler(osapi::Message* msg, unsigned int id);
    osapi::MsgQueue mq_;
    osapi::MsgQueue* mqEntry_;
    osapi::MsgQueue* mqExit_;
    unsigned int carID_;
    bool running_;
};


#endif // CARCLASS_H
