//
// Created by visxim on 7/27/20.
//

#include "shared_memory.h"

bufferstream shared_memory::createSHM(UMGR_s UnSerData, string filename)
{
    filename.erase(filename.length()-5 , 5);
    string SHMfilename = "shm"+filename;

    shared_memory_object::remove(SHMfilename.c_str());
    shared_memory_object shm(open_only, SHMfilename.c_str(), read_write);

    shm.truncate(sizeof(UnSerData)); // 10MiB
    mapped_region region(shm, read_write);

    bufferstream bs(std::ios::out);
    bs.buffer(reinterpret_cast<char*>(region.get_address()), region.get_size());

    // cant return a bufferstream ,needs workaround
    //return bs;
}