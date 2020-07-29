//
// Created by visxim on 7/27/20.
//

#ifndef ADAPTIVEDUMMYPROCESS_SHARED_MEMORY_H
#define ADAPTIVEDUMMYPROCESS_SHARED_MEMORY_H

#include "data_storage.h"
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;

class shared_memory {

private:

public:
    bufferstream createSHM(UMGR_s UnSerData, string filename);
};


#endif //ADAPTIVEDUMMYPROCESS_SHARED_MEMORY_H
