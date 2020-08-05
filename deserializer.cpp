/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  /home/visxim/CLionProjects/AdaptiveDummyProcess/deserializer.cpp
 *        \brief  Deserializer for deserializing the parsed configuration data
 *
 *      \details Deserializer for deserializing data from both shared memory and files
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "deserializer.h"

/*!
* \brief Standard constructor for the deserializer
*
*/
deserializer::deserializer()
{

};

/*!
* \brief Constructor for setting the filename
*
*/
deserializer::deserializer(string name)
{
    filename = name;
};

/*!
* \brief Function for setting the filename
*
*/
void deserializer::setfilename(string name)
{
    filename = name;
};

/*!
* \brief Function for deserializing the struct from a file using iostream
*
*/
void deserializer::deserializeStructFromFile(UMGR_s *Data_s)
{
    //! Erase the ".json" ending and add the "serial" tag
    filename.erase(filename.length()-5,5);
    string SHMfilename = "/home/visxim/CLionProjects/ShareFolder/serial"+filename;

    //! Open an input filestream
    std::ifstream ifs(SHMfilename);

    //! Create an input archive
    boost::archive::binary_iarchive ia(ifs);

    //! Read data from archive
    ia >> *Data_s;

    //! Close input filestream
    ifs.close();
};

/*!
* \brief Function for deserializing the struct from a file using memory mapping
*
*/
void deserializer::deserializeStructFromFileMemMap(UMGR_s *Data_s)
{
    //! Erase the ".json" ending and add the "serial" tag
    filename.erase(filename.length()-5 , 5);
    string binaryfilename = "/home/visxim/CLionProjects/ShareFolder/serial"+filename;

    //! Set the mapped file parameters
    mapped_file_params params;
    params.path          = binaryfilename;
    params.flags         = mapped_file::mapmode::readwrite;

    //! Create a stream with the parameters
    stream<mapped_file> in(params);

    //! Create an input archive
    boost::archive::binary_iarchive ia(in);

    //! Read data from archive
    ia >> *Data_s;

    //! Close stream
    in.close();
};

/*!
* \brief Function for deserializing the struct from a shared memory
*
*/
void deserializer::deserializeStructFromSHM(UMGR_s *Data_s)
{
    //! Erase the ".json" ending and add the "serial" tag
    filename.erase(filename.length()-5 , 5);
    string SHMfilename = "shm"+filename;

    //! Remove the shared memory object if it is still present
    shared_memory_object shm(open_only, SHMfilename.c_str() , read_only);
    //! create the shared memory object
    mapped_region region(shm, read_only);

    //! create the output stream
    bufferstream bs(std::ios::in);
    bs.buffer(reinterpret_cast<char*>(region.get_address()), region.get_size());

    //! create the output archive
    boost::archive::text_iarchive ia(bs);

    //! Serialize the data to the file
    ia >> *Data_s;
};

/*!
 * \brief Not usable because memcpy does only work for POD and string is not a POD type
 *
 * */
void deserializer::copyStructFromSHM(UMGR_s *Data_s)
{
    filename.erase(filename.length()-5 , 5);
    string SHMfilename = "shm"+filename;

    shared_memory_object shm(open_only, SHMfilename.c_str() , read_only);
    mapped_region region(shm, read_only);

    memcpy(Data_s,region.get_address(),sizeof(UMGR_s));
};




