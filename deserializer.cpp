//
// Created by visxim on 7/27/20.
//

#include "deserializer.h"

deserializer::deserializer()
{

};

deserializer::deserializer(string name)
{
    filename = name;
};

void deserializer::setfilename(string name)
{
    filename = name;
};

void deserializer::deserializeStructFromFile(UMGR_s *Data_s)
{
    filename.erase(filename.length()-5,5);
    string SHMfilename = "/home/visxim/CLionProjects/ShareFolder/serial"+filename;

    // create and open an archive for input
    std::ifstream ifs(SHMfilename);
    boost::archive::binary_iarchive ia(ifs);
    // read class state from archive
    ia >> *Data_s;
    // archive and stream closed when destructors are called
    ifs.close();

};

void deserializer::deserializeStructFromFileMemMap(UMGR_s *Data_s)
{
    filename.erase(filename.length()-5 , 5);
    string binaryfilename = "/home/visxim/CLionProjects/ShareFolder/serial"+filename;

    mapped_file_params params;
    params.path          = binaryfilename;
    params.flags         = mapped_file::mapmode::readwrite;

    stream<mapped_file> in(params);

    boost::archive::binary_iarchive ia(in);
    //boost::archive::text_iarchive ia(in);

    ia >> *Data_s;
};

void deserializer::deserializeStructFromSHM(UMGR_s *Data_s)
{
    filename.erase(filename.length()-5 , 5);
    string SHMfilename = "shm"+filename;

    shared_memory_object shm(open_only, SHMfilename.c_str() , read_only);
    mapped_region region(shm, read_only);

    bufferstream bs(std::ios::in);
    bs.buffer(reinterpret_cast<char*>(region.get_address()), region.get_size());
    //std::istringstream bs;

    boost::archive::text_iarchive ia(bs);
    ia >> *Data_s;
};

/*
 * Not usable because memcpy does only work for POD and string is not a POD type
 * */
void deserializer::copyStructFromSHM(UMGR_s *Data_s)
{
    filename.erase(filename.length()-5 , 5);
    string SHMfilename = "shm"+filename;

    shared_memory_object shm(open_only, SHMfilename.c_str() , read_only);
    mapped_region region(shm, read_only);

    memcpy(Data_s,region.get_address(),sizeof(UMGR_s));
};



