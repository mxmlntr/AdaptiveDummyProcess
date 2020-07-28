//
// Created by visxim on 7/27/20.
//

#include "message_manager.h"

message_manager::message_manager()
{

};

int message_manager::openQUEUE(string filename)
{
    filename.erase(filename.length()-5 , 5);
    string QUEUEfilename = filename+"QUEUE";

    //can throw exceptions when queue isnt already created
    msgque.reset(new message_queue(open_only, QUEUEfilename.c_str()));

    cout << "Opened queue named:" << QUEUEfilename << endl;

    return 1;
};

int message_manager::createQUEUE(string filename)
{
    filename.erase(filename.length()-5 , 5);
    string QUEUEfilename = filename+"QUEUE";
    remove(QUEUEfilename.c_str());
    msgque.reset(new message_queue(open_or_create, QUEUEfilename.c_str(), 10, sizeof(int)));

    cout << "Created queue named:" << QUEUEfilename << endl;

    return 1;
};

int message_manager::destroyQUEUE(string filename)
{
    filename.erase(filename.length()-5 , 5);
    string QUEUEfilename = filename+"QUEUE";
    if (msgque->remove(QUEUEfilename.c_str()))
    {
        cout << "Destroyed queue named:" << QUEUEfilename << endl;
        return 1;
    }
    else
    {
        cout << "Could not destroy queue named:" << QUEUEfilename << endl;
        return 0;
    }

};

void message_manager::send_msg(int message,unsigned int priority)
{
    msgque->send(&message,sizeof(int),priority);
};

int message_manager::receive_msg(unsigned int priority)
{
    int message;
    size_t recvd_size;


    if(msgque->timed_receive((void*) &message,sizeof(int),recvd_size,priority,
            boost::posix_time::ptime(microsec_clock::universal_time()) + boost::posix_time::milliseconds(3000)))
    {
        cout << "Message successfully received." << endl;
        return message;
    }
    else
    {
        cout << "TIMEOUT: MessageQueue." << endl;
        return 0;
    }

};

size_t message_manager::CheckNumOfMsg()
{
    return msgque->get_num_msg();
};