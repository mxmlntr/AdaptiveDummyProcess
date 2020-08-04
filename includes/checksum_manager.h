/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/includes/checksum_manager.h
 *        \brief  Header of checksum_manager for checking the integrity of the data
 *
 *      \details The Checksum_manager creates and checks if the data is valid
 *
 *
 *********************************************************************************************************************/
#ifndef ADAPTIVEDUMMYPROCESS_CHECKSUM_MANAGER_H
#define ADAPTIVEDUMMYPROCESS_CHECKSUM_MANAGER_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "data_storage.h"
#include "boost/crc.hpp"
#include "iostream"

using namespace boost;

/*!
 * \brief Class of checksum manager for CRC managment
 */
class checksum_manager{

private:

public:
    int createCRC(UMGR_s *CRCdata);
    int checkCRC(UMGR_s *CRCdata);

};

#endif //ADAPTIVEDUMMYPROCESS_CHECKSUM_MANAGER_H
