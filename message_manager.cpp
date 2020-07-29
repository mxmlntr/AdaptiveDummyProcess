//
// Created by visxim on 7/27/20.
//

#include "message_manager.h"

message_manager::message_manager()
{

};

/*
 * This method shall be used by the receiving processes only because the daemon will create the queues
 * */
int message_manager::openQUEUE(string filename)
{
    filename.erase(filename.length()-5 , 5);
    string PtoDfilename = filename+"QUEUE_ProcesstoDaemon";
    string DtoPfilename = filename+"QUEUE_DaemontoProcess";

    //can throw exceptions when queue isnt already created
    msgqueSEND.reset(new message_queue(open_only, PtoDfilename.c_str()));
    cout << "Opened queue named:" << PtoDfilename << endl;

    msgqueRECEIVE.reset(new message_queue(open_only, DtoPfilename.c_str()));
    cout << "Opened queue named:" << DtoPfilename << endl;

    return 1;
};

/*
 * This method shall be used by the daemon only
 * */
int message_manager::createQUEUE(string filename)
{
    filename.erase(filename.length()-5 , 5);
    string PtoDfilename = filename+"QUEUE_ProcesstoDaemon";
    string DtoPfilename = filename+"QUEUE_DaemontoProcess";

    remove(PtoDfilename.c_str());
    remove(DtoPfilename.c_str());

    msgqueSEND.reset(new message_queue(open_or_create, DtoPfilename.c_str(), 10, sizeof(int)));
    cout << "Created queue named:" << DtoPfilename << endl;
    msgqueRECEIVE.reset(new message_queue(open_or_create, PtoDfilename.c_str(), 10, sizeof(int)));
    cout << "Created queue named:" << PtoDfilename << endl;

    return 1;
};

/*
 * This method shall be used by the daemon only
 * */
int message_manager::destroyQUEUE(string filename)
{
    filename.erase(filename.length()-5 , 5);
    string PtoDfilename = filename+"QUEUE_ProcesstoDaemon";
    string DtoPfilename = filename+"QUEUE_DaemontoProcess";
    if (msgqueSEND->remove(PtoDfilename.c_str()) && msgqueRECEIVE->remove(DtoPfilename.c_str()))
    {
        cout << "Destroyed queue named:" << PtoDfilename << endl;
        cout << "Destroyed queue named:" << DtoPfilename << endl;
        return 1;
    }
    else
    {
        cout << "ERROR: While destroying queues." << endl;
        return 0;
    }
};

void message_manager::send_msg(int message,unsigned int priority)
{
    msgqueSEND->send(&message,sizeof(int),priority);
};

int message_manager::receive_msg(unsigned int priority)
{
    int message;
    size_t recvd_size;
    if(msgqueRECEIVE->timed_receive((void*) &message,sizeof(int),recvd_size,priority,
                                    boost::posix_time::ptime(microsec_clock::universal_time()) + boost::posix_time::milliseconds(1000)))
    {
        //cout << "Message successfully received." << endl;
        return message;
    }
    else
    {
        //cout << "TIMEOUT: MessageQueue." << endl;
        return 0;
    }
};

size_t message_manager::CheckNumOfMsgSEND()
{
    return msgqueSEND->get_num_msg();
};

size_t message_manager::CheckNumOfMsgRECEIVE()
{
    return msgqueRECEIVE->get_num_msg();
};