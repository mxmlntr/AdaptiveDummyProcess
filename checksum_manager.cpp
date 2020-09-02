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
    return CRCdata->calcCRC();
};

/*!
 * \brief Function for creating the checksum
 *
 * Needs to be overloaded for different data structures
 * */
int checksum_manager::createCRC(EXMPLE_s *CRCdata)
{
    //! Process all bytes of the struct
    crc_32_type crc;

    return crc.checksum();
};

/*!
 * \brief Function for checking the checksum
 *
 * Needs to be overloaded for different data structures
 * */
int checksum_manager::checkCRC(EXMPLE_s *CRCdata)
{
    //! Process all bytes of the struct
    crc_32_type crc;

    //! Compare the received checksum with the self calculated
    if(crc.checksum() == CRCdata->checksum)
    {
        return 1;
    }
    return 0;
};

/*!
 * \brief Function for checking the checksum
 *
 * Needs to be overloaded for different data structures
 * */
int checksum_manager::checkCRC(UMGR_s *CRCdata)
{
    //! Compare the received checksum with the self calculated
    if(CRCdata->calcCRC() == CRCdata->checksum)
    {
        return 1;
    }
    return 0;
};