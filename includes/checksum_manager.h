//
// Created by visxim on 7/27/20.
//

#ifndef ADAPTIVEDUMMYPROCESS_CHECKSUM_MANAGER_H
#define ADAPTIVEDUMMYPROCESS_CHECKSUM_MANAGER_H

#include "data_storage.h"
#include "boost/crc.hpp"
#include "iostream"

// Redefine this to change to processing buffer size
#define PRIVATE_BUFFER_SIZE  1024
// Global objects
std::streamsize const  buffer_size = PRIVATE_BUFFER_SIZE;

class checksum_manager{

private:

public:
    int createCRC(UMGR_s *CRCdata);

};

#endif //ADAPTIVEDUMMYPROCESS_CHECKSUM_MANAGER_H
