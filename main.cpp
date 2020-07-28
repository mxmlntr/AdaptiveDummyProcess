//
// Created by visxim on 7/27/20.
//

#include <iostream>
#include "message_manager.h"

message_manager mesQ;

int main()
{
    mesQ.createQUEUE("UMGR.json");
    //mesQ.send_msg(5555,1);
    int recvmsg = mesQ.receive_msg(20);
    if(recvmsg)
    {
        cout << "received:" << recvmsg << endl;
    }


    return 0;
}
