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
    //! Process all bytes of the struct
    crc_32_type crc;
    crc.process_bytes(CRCdata->name.data(), CRCdata->name.size());
    crc.process_bytes(CRCdata->description.data(), CRCdata->description.size());
    crc.process_bytes(CRCdata->dlt_id.data(), CRCdata->dlt_id.size());
    crc.process_bytes(CRCdata->log_mode.data(), CRCdata->log_mode.size());
    crc.process_bytes(CRCdata->log_level.data(), CRCdata->log_level.size());
    crc.process_bytes(CRCdata->log_dir_path.data(), CRCdata->log_dir_path.size());
    crc.process_block(&CRCdata->ipc_port, &CRCdata->ipc_port+1);
    crc.process_block(&CRCdata->reconnection_retry_offset, &CRCdata->reconnection_retry_offset+1);
    crc.process_block(&CRCdata->msg_buf_size, &CRCdata->msg_buf_size+1);

    return crc.checksum();
};

/*!
 * \brief Function for checking the checksum
 *
 * Needs to be overloaded for different data structures
 * */
int checksum_manager::checkCRC(UMGR_s *CRCdata)
{
    //! Process all bytes of the struct
    crc_32_type crc;
    crc.process_bytes(CRCdata->name.data(), CRCdata->name.size());
    crc.process_bytes(CRCdata->description.data(), CRCdata->description.size());
    crc.process_bytes(CRCdata->dlt_id.data(), CRCdata->dlt_id.size());
    crc.process_bytes(CRCdata->log_mode.data(), CRCdata->log_mode.size());
    crc.process_bytes(CRCdata->log_level.data(), CRCdata->log_level.size());
    crc.process_bytes(CRCdata->log_dir_path.data(), CRCdata->log_dir_path.size());
    crc.process_block(&CRCdata->ipc_port, &CRCdata->ipc_port+1);
    crc.process_block(&CRCdata->reconnection_retry_offset, &CRCdata->reconnection_retry_offset+1);
    crc.process_block(&CRCdata->msg_buf_size, &CRCdata->msg_buf_size+1);

    //! Compare the received checksum with the self calculated
    if(crc.checksum() == CRCdata->checksum)
    {
        return 1;
    }
    return 0;
};