/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/includes/message_manager.h
 *        \brief  Header of message_manager for managing the synchronization between processes
 *
 *      \details The message_manager managed all synchronization between processes via message queue
 *
 *
 *********************************************************************************************************************/
#ifndef ADAPTIVEDUMMYPROCESS_MESSAGE_MANAGER_H
#define ADAPTIVEDUMMYPROCESS_MESSAGE_MANAGER_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <iostream>
#include "boost/interprocess/ipc/message_queue.hpp"
#include "boost/scoped_ptr.hpp"
#include "data_storage.h"

using namespace boost::interprocess;

/*!
 * \brief Class of message manager which handles the synchronization between processes
 */
class message_manager
{
private:
    std::unique_ptr<message_queue> msgqueSEND;
    std::unique_ptr<message_queue> msgqueRECEIVE;
public:
    message_manager();
    void send_msg(int message, unsigned int priority);
    int receive_msg(unsigned int priority);
    int openQUEUE(string filename);
    int createQUEUE(string filename);
    int destroyQUEUE(string filename);
    size_t CheckNumOfMsgSEND();
    size_t CheckNumOfMsgRECEIVE();
};

#endif //ADAPTIVEDUMMYPROCESS_MESSAGE_MANAGER_H
