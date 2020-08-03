//
// Created by visxim on 7/27/20.
//

#include <iostream>
#include "message_manager.h"
#include "deserializer.h"
#include "checksum_manager.h"

#define PRIORITY 1

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

message_manager mesQ;
deserializer des("UMGR.json");
checksum_manager crc;

int main()
{
    UMGR_s receivedData;

    mesQ.openQUEUE("UMGR.json");
    mesQ.send_msg(ProcessReady,PRIORITY);

    int recvmsg = mesQ.receive_msg(PRIORITY);

    switch(recvmsg)
    {
        case DataRdySHM:
            cout << "Receiving data from SHM." << endl;
            des.deserializeStructFromSHM(&receivedData);
            crc.createCRC(&receivedData);
            cout << "Received via SHM:" << receivedData.name << endl;
            mesQ.send_msg(DataReceiveSuccess,PRIORITY);
            break;
        case DataRdyFile:
            cout << "Receiving data from file." << endl;
            des.deserializeStructFromFileMemMap(&receivedData);
            crc.createCRC(&receivedData);
            cout << "Received via file:" << receivedData.name << endl;
            mesQ.send_msg(DataReceiveSuccess,PRIORITY);
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
