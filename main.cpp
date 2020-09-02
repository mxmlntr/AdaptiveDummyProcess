/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/main.cpp
 *        \brief  main of the AdaptiveDummyProcess
 *
 *      \details
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <iostream>
#include "message_manager.h"
#include "deserializer.h"
#include "checksum_manager.h"
#include "time-tp.h"

//! MessageQueue Priority
#define PRIORITY 1
#define EXMPLE
//#define UMGR

/**********************************************************************************************************************
 *  OBJECT DECLARATION
 *********************************************************************************************************************/

//! Enum for synchronization via message queue
enum SyncMsg
{
    ProcessTimeout = 00,
    ProcessReady = 11,
    DataRdySHM = 22,
    DataRdyFile = 33,
    DataReceiveSuccess = 44,
    DataErrorCRC = 55,
    ReceivingError = 66,
    DaemonTimeout = 77
};


int main(int argc, char **argv)
{
#ifdef EXMPLE
    message_manager mesQ;
    deserializer des("EXMPLE.json");
    checksum_manager checksum;

    //! Create a struct for the received data
    EXMPLE_s receivedData;

    //! Open the message queue for synchronization
    mesQ.openQUEUE("EXMPLE.json");

    //! Notify the daemon that the process is ready for receiption
    mesQ.send_msg(ProcessReady,PRIORITY);

    //! Receive message and evaluate
    int recvmsg = mesQ.receive_msg(PRIORITY);
#endif

#ifdef UMGR
    message_manager mesQ;
    deserializer des("UMGR.json");
    checksum_manager checksum;

    //! Create a struct for the received data
    UMGR_s receivedData;

    //! Open the message queue for synchronization
    mesQ.openQUEUE("UMGR.json");

    //! Notify the daemon that the process is ready for receiption
    mesQ.send_msg(ProcessReady,PRIORITY);

    //! Receive message and evaluate
    int recvmsg = mesQ.receive_msg(PRIORITY);
#endif

#ifdef TRACENEWFILE
    tracepoint(tp_provider, time_tracepoint_dummy_new, 6);
#endif

#ifdef TRACEOLDFILE
    tracepoint(tp_provider, time_tracepoint_dummy_old, 2);
#endif

    switch(recvmsg)
    {
        case DataRdySHM:
            cout << "Receiving data from SHM." << endl;
            des.deserializeStructFromSHM(&receivedData);
#ifdef TRACENEWFILE
            tracepoint(tp_provider, time_tracepoint_dummy_new, 7);
#endif
            if(checksum.checkCRC(&receivedData))
            {
#ifdef EXMPLE
                cout << "Received via SHM:" << receivedData.name0 << endl;
#endif
#ifdef UMGR
                cout << "Received via SHM:" << receivedData.name << endl;
#endif
#ifdef TRACENEWFILE
                tracepoint(tp_provider, time_tracepoint_dummy_new, 8);
#endif
                mesQ.send_msg(DataReceiveSuccess,PRIORITY);

            } else
            {
                cout << "CRC error." << endl;
                mesQ.send_msg(DataErrorCRC,PRIORITY);
            }
            break;
        case DataRdyFile:
            cout << "Receiving data from file." << endl;
#ifdef UMGR
            des.setfilename("UMGR.json");
#endif

#ifdef EXMPLE
            des.setfilename("EXMPLE.json");
#endif

            des.deserializeStructFromFileMemMap(&receivedData);

#ifdef TRACEOLDFILE
            tracepoint(tp_provider, time_tracepoint_dummy_old, 3);
#endif
            if(checksum.checkCRC(&receivedData))
            {
#ifdef EXMPLE
                cout << "Received via file:" << receivedData.name0 << endl;
#endif
#ifdef UMGR
                cout << "Received via file:" << receivedData.name << endl;
#endif
#ifdef TRACEOLDFILE
                tracepoint(tp_provider, time_tracepoint_dummy_old, 4);
#endif
                mesQ.send_msg(DataReceiveSuccess,PRIORITY);
            } else
            {
                cout << "CRC error." << endl;
                mesQ.send_msg(DataErrorCRC,PRIORITY);
            }
            break;
        case ProcessTimeout:
            cout << "Connection to Process UMGR timed out." << endl;
            mesQ.send_msg(DaemonTimeout,PRIORITY);
            break;
        default:
            cout << "Daemon replied with unknown message." << recvmsg << endl;
            mesQ.send_msg(ReceivingError,PRIORITY);
            break;
    }
    return 0;
}