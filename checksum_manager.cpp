//
// Created by visxim on 7/27/20.
//

#include "checksum_manager.h"

/*
 * Needs to be overloaded for different data structures
 *
 * */
int checksum_manager::createCRC(UMGR_s *CRCdata)
{
    boost::crc_32_type result;

    result.process_block(CRCdata, CRCdata + 1);

    cout << result.checksum() << endl;

    return result.checksum();
};