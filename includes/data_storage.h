//
// Created by visxim on 7/27/20.
//

#ifndef ADAPTIVEDUMMYPROCESS_DATA_STORAGE_H
#define ADAPTIVEDUMMYPROCESS_DATA_STORAGE_H

#include <fstream>
#include <string>
#include <stdint.h>

using namespace std;

/*
 * Struct which is specified to hold the values of the UpdateManager UMGR
 */
typedef struct{
    string name;
    string description;
    string dlt_id;
    string log_mode;
    string log_level;
    string log_dir_path;
    uint ipc_port;
    uint reconnection_retry_offset;
    uint msg_buf_size;
    int checksum;

    //function for serializing the struct
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & name;
        ar & description;
        ar & dlt_id;
        ar & log_mode;
        ar & log_level;
        ar & log_dir_path;
        ar & ipc_port;
        ar & reconnection_retry_offset;
        ar & msg_buf_size;
        ar & checksum;
    }
} UMGR_s;

#endif //ADAPTIVEDUMMYPROCESS_DATA_STORAGE_H
