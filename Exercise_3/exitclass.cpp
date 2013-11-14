#include <iostream>
#include "exitclass.h"

using namespace std;

ExitClass::ExitClass(EntryClass* entry) : mq_(MSGQUEUE_SIZE)
{
    mqEntry_ = entry->getMsgQueue();
    running_ = true;
}

void ExitClass::run()
{
    while(running_)
    {
        unsigned long id;
        osapi::Message* msg = mq_.receive(id);
        handler(msg, id);
        delete msg;
    }
}

void ExitClass::handler(osapi::Message* msg, unsigned int id)
{
    switch(id)
    {
        case ID_EXIT_OPEN_REQ:
        {
            // Car is requesting to exit, generate event to tell them it's confirmed
            ExitOpenReq* req = static_cast<ExitOpenReq*>(msg);
            ExitOpenCfm* cfm = new ExitOpenCfm;
            cout << "- Exit Guard: Now letting car " << req->carID << " out." << endl;
            req->msgQueue->send(ID_EXIT_OPEN_CFM, cfm);
            break;
        }

        case ID_EXIT_OUTSIDE_IND:
        {
            // Car indicated it has left the parking lot, so tell Entry Guard that a new spot is
            EntryNewSpotInd* ind = new EntryNewSpotInd;
            mqEntry_->send(ID_ENTRY_NEW_SPOT, ind);
            break;
        }
        default:
            cout << "Handler received unknown identifier: " << id << endl;
    }
}

osapi::MsgQueue* ExitClass::getMsgQueue()
{
    return &mq_;
}
