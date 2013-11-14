#include <iostream>
#include "entryclass.h"

using namespace std;

EntryClass::EntryClass() : mq_(MSGQUEUE_SIZE),
                           mqIntern_(MSGQUEUE_SIZE)
{
    parkingSpots_ = PARKING_SPOTS;
    carsWaiting_ = 0;
    running_ = true;
}

void EntryClass::run()
{
    while(running_)
    {
        unsigned long id;
        osapi::Message* msg = mq_.receive(id);
        handler(msg, id);
        delete msg;
    }
}

void EntryClass::handler(osapi::Message* msg, unsigned int id)
{
    switch(id)
    {
        case ID_ENTRY_OPEN_REQ:
        {
            EntryOpenReq* req = static_cast<EntryOpenReq*>(msg);

            if (parkingSpots_ > 0)   // If there is space, let the car in
            {
                parkingSpots_--;
                EntryOpenCfm* cfm = new EntryOpenCfm;
                cout << "+ Entry Guard: Now letting car " << req->carID << " in."
                     << " (" << parkingSpots_ << " spots left)" << endl;
                req->msgQueue->send(ID_ENTRY_OPEN_CFM, cfm);
            }
            else    // There is no space, so put the car into the intern waiting queue
            {
                carsWaiting_++;
                InternQueueReq* internReq = new InternQueueReq;
                internReq->carID = req->carID;
                internReq->msgQueue = req->msgQueue;
                cout << "  Entry Guard: Car " << req->carID << " must wait for a spot." << endl;
                mqIntern_.send(ID_INTERN_QUEUE, internReq);
            }
            break;
        }

        case ID_ENTRY_NEW_SPOT:
        {
            // Car left the parking lot
            parkingSpots_++;
            cout << "  Entry Guard: Message from Exit Guard - Car has left."
                 << " (" << parkingSpots_ << " spots left)" << endl;
            if (carsWaiting_ > 0)    // Handle the intern waiting queue
            {
                carsWaiting_--;
                // Read from internal waiting queue
                unsigned long id;
                osapi::Message* msg = mqIntern_.receive(id);
                EntryOpenReq* req = static_cast<EntryOpenReq*>(msg);

                // Send new event for the waiting car
                EntryOpenReq* newReq = new EntryOpenReq;
                newReq->msgQueue = req->msgQueue;
                newReq->carID = req->carID;

                mq_.send(ID_ENTRY_OPEN_REQ, newReq);
            }
            break;
        }
        default:
            cout << "Handler received unknown identifier: " << id << endl;
    }
}

osapi::MsgQueue* EntryClass::getMsgQueue()
{
    return &mq_;
}
