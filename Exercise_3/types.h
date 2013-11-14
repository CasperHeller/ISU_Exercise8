#ifndef MSGTYPES_H
#define MSGTYPES_H

#include "osapi/MsgQueue.hpp"

// Constants
const int PARKING_SPOTS = 3;
const int MSGQUEUE_SIZE = 10;
const int SLEEP_TIME = 5000;        // Sleep time in ms

// Enum with all message ID's
enum
{
    ID_ENTRY_OPEN_REQ,
    ID_ENTRY_OPEN_CFM,
    ID_ENTRY_NEW_SPOT,
    ID_EXIT_OPEN_REQ,
    ID_EXIT_OPEN_CFM,
    ID_EXIT_OUTSIDE_IND,
    ID_INTERN_QUEUE
};

struct EntryOpenReq : public osapi::Message
{
    osapi::MsgQueue* msgQueue;
    unsigned long carID;
};

struct EntryOpenCfm: public osapi::Message
{};

struct EntryNewSpotInd: public osapi::Message
{
    unsigned long carID;
};

struct ExitOpenReq : public osapi::Message
{
    osapi::MsgQueue* msgQueue;
    unsigned long carID;
};

struct ExitOpenCfm: public osapi::Message
{};

struct ExitOutsideInd : public osapi::Message
{
    unsigned long carID;
};

struct InternQueueReq : public osapi::Message
{
    osapi::MsgQueue* msgQueue;
    unsigned long carID;
};


#endif // MSGTYPES_H
