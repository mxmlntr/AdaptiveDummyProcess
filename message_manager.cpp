/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/message_manager.cpp
 *        \brief  Message_manager for managing the synchronization between processes
 *
 *      \details The Message_manager managed all synchronization between processes via message queue
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "message_manager.h"

/*!
* \brief Standard constructor for the message_manager
*
*/
message_manager::message_manager()
{

};

/*!
 * \brief Method for opening the message queue
 *
 *  This method shall be used by the receiving processes only because the daemon will create the queues
 * */
int message_manager::openQUEUE(string filename)
{
    //! Erase the ".json" ending and create the message queue name for unambiguous identification
    filename.erase(filename.length()-5 , 5);
    string PtoDfilename = filename+"QUEUE_ProcesstoDaemon";
    string DtoPfilename = filename+"QUEUE_DaemontoProcess";

    //!can throw exceptions when queue isnt already created
    msgqueSEND.reset(new message_queue(open_or_create, DtoPfilename.c_str(), 10, sizeof(int)));
    cout << "Opened queue named:" << PtoDfilename << endl;

    msgqueRECEIVE.reset(new message_queue(open_or_create, DtoPfilename.c_str(), 10, sizeof(int)));
    cout << "Opened queue named:" << DtoPfilename << endl;

    return 1;
};

/*!
 * \brief Method for creating the message queue
 *
 *  This method shall be used by the daemon only
 * */
int message_manager::createQUEUE(string filename)
{
    //! Erase the ".json" ending and create the message queue name for unambiguous identification
    filename.erase(filename.length()-5 , 5);
    string PtoDfilename = filename+"QUEUE_ProcesstoDaemon";
    string DtoPfilename = filename+"QUEUE_DaemontoProcess";

    //! Remove previous message queue
    remove(PtoDfilename.c_str());
    remove(DtoPfilename.c_str());

    //! Create message queues
    msgqueSEND.reset(new message_queue(open_or_create, DtoPfilename.c_str(), 10, sizeof(int)));
    cout << "Created queue named:" << DtoPfilename << endl;
    msgqueRECEIVE.reset(new message_queue(open_or_create, PtoDfilename.c_str(), 10, sizeof(int)));
    cout << "Created queue named:" << PtoDfilename << endl;

    return 1;
};

/*!
 * \brief Method for destroying the message queues
 *
 * This method shall be used by the daemon only
 * */
int message_manager::destroyQUEUE(string filename)
{
    //! Erase the ".json" ending and create the message queue name for unambiguous identification
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

/*!
 * \brief Send a message
 *
 * */
void message_manager::send_msg(int message,unsigned int priority)
{
    msgqueSEND->send(&message,sizeof(int),priority);
};

/*!
 * \brief Receive a message
 *
 * */
int message_manager::receive_msg(unsigned int priority)
{
    int message;
    size_t recvd_size;
    //! The timed receive is handled by the BOOST library and is implemented by a mutex with condition
    if(msgqueRECEIVE->timed_receive((void*) &message,sizeof(int),recvd_size,priority,
                                    boost::posix_time::ptime(microsec_clock::universal_time()) + boost::posix_time::milliseconds(9000)))
    {
        //cout << "Message successfully received." << endl;
        return message;
    }
    else
    {
        cout << "TIMEOUT: MessageQueue." << endl;
        return 0;
    }
};

/*!
 * \brief Check Nnumber of messages in the sender queue
 *
 * */
size_t message_manager::CheckNumOfMsgSEND()
{
    return msgqueSEND->get_num_msg();
};

/*!
 * \brief Check Nnumber of messages in the receiver queue
 *
 * */
size_t message_manager::CheckNumOfMsgRECEIVE()
{
    return msgqueRECEIVE->get_num_msg();
};