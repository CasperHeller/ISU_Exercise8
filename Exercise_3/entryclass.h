#ifndef ENTRYCLASS_H
#define ENTRYCLASS_H

#include "osapi/Thread.hpp"
#include "osapi/MsgQueue.hpp"
#include "types.h"


class EntryClass : public osapi::ThreadFunctor
{
public:
    EntryClass();
    void run();
    osapi::MsgQueue* getMsgQueue();
private:
    void handler(osapi::Message* msg, unsigned int id);
    osapi::MsgQueue mq_;
    osapi::MsgQueue mqIntern_;
    unsigned int parkingSpots_;
    unsigned int carsWaiting_;

    bool running_;
};

#endif // ENTRYCLASS_H
