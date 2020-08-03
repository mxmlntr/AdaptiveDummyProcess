/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/checksum_manager.cpp
 *        \brief  Checksum_manager for checking the integrity of the data
 *
 *      \details The Checksum_manager creates and checks if the data is valid
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "checksum_manager.h"

/*!
 * \brief Function for creating the checksum
 *
 * Needs to be overloaded for different data structures
 * */
int checksum_manager::createCRC(UMGR_s *CRCdata)
{
    boost::crc_32_type result;

    cout << &CRCdata->name << " value: " <<  CRCdata->name  << endl;
    cout << &CRCdata->description << " value: " <<  CRCdata->description  << endl;
    cout << &CRCdata->dlt_id << " value: " <<  CRCdata->dlt_id  << endl;
    cout << &CRCdata->log_mode << " value: " <<  CRCdata->log_mode  << endl;
    cout << &CRCdata->log_level << " value: " <<  CRCdata->log_level  << endl;
    cout << &CRCdata->log_dir_path << " value: " <<  CRCdata->log_dir_path << endl;
    cout << &CRCdata->ipc_port << " value: " <<  CRCdata->ipc_port  << endl;
    cout << &CRCdata->reconnection_retry_offset << " value: " <<  CRCdata->reconnection_retry_offset  << endl;
    cout << &CRCdata->msg_buf_size << " value: " <<  CRCdata->msg_buf_size  << endl;
    cout << &CRCdata->checksum << " value: " <<  CRCdata->checksum  << endl;

    result.process_block(&CRCdata->name, &CRCdata->checksum);

    cout << "Checksum: " <<result.checksum() << endl;

    cout << sizeof(string) << endl;
    cout << sizeof(unsigned int) << endl;
    cout << sizeof(int) << endl;

    return result.checksum();

    union tWandler
    {
        struct
        {
            char hi;
            char lo;
        } byte;
    } Wandler;

    Wandler.byte.hi = 'a';
    Wandler.byte.lo = 'b';

    result.process_block(&Wandler.byte.hi, &Wandler.byte.lo);
    cout << "CRC: " << result.checksum() << endl;
    return 1;

};

/*!
 * \brief Function for checking the checksum
 *
 * Needs to be overloaded for different data structures
 * */
int checksum_manager::checkCRC(UMGR_s *CRCdata)
{

};