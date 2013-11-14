#ifndef EXITCLASS_H
#define EXITCLASS_H

#include "osapi/Thread.hpp"
#include "osapi/MsgQueue.hpp"
#include "types.h"
#include "entryclass.h"

class ExitClass : public osapi::ThreadFunctor
{
public:
    ExitClass(EntryClass* entry);
    void run();
    osapi::MsgQueue* getMsgQueue();
private:
    void handler(osapi::Message* msg, unsigned int id);
    osapi::MsgQueue mq_;
    osapi::MsgQueue* mqEntry_;
    bool running_;
};

#endif // EXITCLASS_H
