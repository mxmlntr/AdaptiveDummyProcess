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
#ifdef TRACENEWFILE
    tracepoint(tp_provider, time_tracepoint_dummy, 6);
#endif
#ifdef TRACEOLDFILE
    tracepoint(tp_provider, time_tracepoint_dummy, 2);
#endif
    switch(recvmsg)
    {
        case DataRdySHM:
            cout << "Receiving data from SHM." << endl;
            des.deserializeStructFromSHM(&receivedData);
#ifdef TRACENEWFILE
            tracepoint(tp_provider, time_tracepoint_dummy, 7);
#endif
            if(checksum.checkCRC(&receivedData))
            {
                cout << "Received via SHM:" << receivedData.name << endl;
#ifdef TRACENEWFILE
                tracepoint(tp_provider, time_tracepoint_dummy, 8);
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
            des.setfilename("UMGR.json");
            des.deserializeStructFromFileMemMap(&receivedData);
#ifdef TRACEOLDFILE
            tracepoint(tp_provider, time_tracepoint_dummy, 3);
#endif
            if(checksum.checkCRC(&receivedData))
            {
                cout << "Received via file:" << receivedData.name << endl;
#ifdef TRACEOLDFILE
                tracepoint(tp_provider, time_tracepoint_dummy, 4);
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
