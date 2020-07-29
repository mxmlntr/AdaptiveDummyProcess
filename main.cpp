//
// Created by visxim on 7/27/20.
//

#include <iostream>
#include "message_manager.h"
#include "deserializer.h"

message_manager mesQ;
deserializer des("UMGR.json");

int main()
{
    UMGR_s receivedData;

    mesQ.openQUEUE("UMGR.json");
    mesQ.send_msg(1111,1);

    int recvmsg = mesQ.receive_msg(1);
    if(recvmsg == 2222)
    {
        cout << "received:" << recvmsg << endl;
        des.deserializeStructFromSHM(&receivedData);
        cout << "received via SHM:" << receivedData.description << endl;
        mesQ.send_msg(9999,1);
    }
    else if (recvmsg == 3333)
    {
        cout << "received:" << recvmsg << endl;
        des.deserializeStructFromFileMemMap(&receivedData);
        cout << "received via MemMap:" << receivedData.description << endl;
        mesQ.send_msg(9999,1);
    }
    else
    {
        cout << "received unknown message:" << recvmsg << endl;
    }
    return 0;
}
