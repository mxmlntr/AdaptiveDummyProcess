/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/includes/deserializer.h
 *        \brief  Header of deserializer for deserializing the parsed configuration data
 *
 *      \details Deserializer for deserializing data from both shared memory and files
 *
 *
 *********************************************************************************************************************/
#ifndef ADAPTIVEDUMMYPROCESS_DESERIALIZER_H
#define ADAPTIVEDUMMYPROCESS_DESERIALIZER_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "data_storage.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/iostreams/device//mapped_file.hpp>
#include <boost/iostreams/stream.hpp>

using namespace boost::interprocess;
using namespace boost::iostreams;

/*!
 * \brief Class of deserializer which handles deserialization of data from files and shared memory
 */
class deserializer{
private:
    string filename;
public:
    deserializer();
    deserializer(string name);
    void setfilename(string name);

    //!This method is overloaded for every struct in data_storage
    void deserializeStructFromSHM(UMGR_s *Data_s);
    void deserializeStructFromSHM(EXMPLE_s *Data_s);

    //!This method is overloaded for every struct in data_storage
    void deserializeStructFromFileMemMap(UMGR_s *Data_s);
    void deserializeStructFromFileMemMap(EXMPLE_s *Data_s);

    //!This method was replaced by the MemMap version
    void deserializeStructFromFile(UMGR_s *Data_s);
    void deserializeStructFromFile(EXMPLE_s *Data_s);
    //!Unused
    void copyStructFromSHM(UMGR_s *Data_s);
};

#endif //ADAPTIVEDUMMYPROCESS_DESERIALIZER_H
