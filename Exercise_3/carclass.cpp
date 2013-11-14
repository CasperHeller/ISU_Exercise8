#include <iostream>
#include "carclass.h"
#include "osapi/Utility.hpp"

using namespace std;

CarClass::CarClass(EntryClass* entry, ExitClass* exit, unsigned int carID) : mq_(MSGQUEUE_SIZE)
{
    mqEntry_ = entry->getMsgQueue();
    mqExit_ = exit->getMsgQueue();

    carID_ = carID;

    running_ = true;

    EntryOpenReq* req = new EntryOpenReq;
    req->carID = carID_;
    req->msgQueue = &mq_;
    mqEntry_->send(ID_ENTRY_OPEN_REQ, req);
}

void CarClass::run()
{
    while(running_)
    {
        unsigned long id;
        osapi::Message* msg = mq_.receive(id);
        handler(msg, id);
        delete msg;
    }
}

void CarClass::handler(osapi::Message* msg, unsigned int id)
{
    switch(id)
    {
        case ID_ENTRY_OPEN_CFM:
        {
            // Car is now inside parking lot, wait before exiting (SLEEP_TIME is in seconds)
            osapi::sleep(rand()%SLEEP_TIME+1);

            // Trying to exit now, generate event for Exit Guard
            ExitOpenReq* req = new ExitOpenReq;
            req->carID = carID_;
            req->msgQueue = &mq_;
            // Send event
            mqExit_->send(ID_EXIT_OPEN_REQ, req);
            break;
        }
        case ID_EXIT_OPEN_CFM:
        {
            // Car is now outside parking lot, send event to Exit Guard that we've left
            ExitOutsideInd* ind = new ExitOutsideInd;
            ind->carID = carID_;
            mqExit_->send(ID_EXIT_OUTSIDE_IND, ind);

            // Now sleeping (SLEEP_TIME is in seconds)
            osapi::sleep(rand()%SLEEP_TIME+1);

            // Trying to re-enter now
            EntryOpenReq* req = new EntryOpenReq;
            req->carID = carID_;
            req->msgQueue = &mq_;

            mqEntry_->send(ID_ENTRY_OPEN_REQ, req);
            break;
        }
        default:
            cout << "Handler received unknown identifier: " << id << endl;
    }
}
