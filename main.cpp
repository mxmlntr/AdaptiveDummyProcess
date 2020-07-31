//
// Created by visxim on 7/27/20.
//

#include <iostream>
#include "message_manager.h"
#include "deserializer.h"

#define PRIORITY 1

enum SyncMsg
{
    ProcessReady = 11,
    DataRdySHM = 22,
    DataRdyFile = 33,
    DataReceiveSuccess = 44,
    DataErrorCRC = 55,
    ReceivingError = 66
};

message_manager mesQ;
deserializer des("UMGR.json");

int main()
{
    UMGR_s receivedData;

    mesQ.openQUEUE("UMGR.json");
    mesQ.send_msg(ProcessReady,PRIORITY);

    int recvmsg = mesQ.receive_msg(PRIORITY);
    if(recvmsg == DataRdySHM)
    {
        cout << "Receiving data from SHM." << endl;
        des.deserializeStructFromSHM(&receivedData);
        cout << "Received via SHM:" << receivedData.name << endl;
        mesQ.send_msg(DataReceiveSuccess,PRIORITY);
    }
    else if (recvmsg == DataRdyFile)
    {
        cout << "Receiving data from file." << endl;
        des.deserializeStructFromFileMemMap(&receivedData);
        cout << "Received via file:" << receivedData.name << endl;
        mesQ.send_msg(DataReceiveSuccess,PRIORITY);
    }
    else
    {
        cout << "Received unknown message:" << recvmsg << endl;
        mesQ.send_msg(ReceivingError,PRIORITY);
    }
    return 0;
}
