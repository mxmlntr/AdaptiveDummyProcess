cmake_minimum_required(VERSION 3.16)
project(AdaptiveDummyProcess)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
SET(PLATFORM_SPECIFIC_LIBS "-lpthread")

add_executable(AdaptiveDummyProcess main.cpp deserializer.cpp includes/deserializer.h includes/data_storage.h checksum_manager.cpp includes/checksum_manager.h shared_memory.cpp includes/shared_memory.h message_manager.cpp includes/message_manager.h includes/time-tp.h time-tp.cpp)

include_directories(~/CLionProjects/AdaptiveDummyProcess/includes/
        ~/CLionProjects/AdaptiveDummyProcess/includes/rapidjson
        ~/CLionProjects/AdaptiveDummyProcess/
        ~/home/visxim/boost_1_73_0/)

find_library(LIB_RT rt
        )

target_link_libraries(${PROJECT_NAME}
        libboost_serialization.a
        libboost_iostreams.a
        ${LIB_RT}
        lttng-ust
        dl
        )