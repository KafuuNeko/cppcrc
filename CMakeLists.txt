cmake_minimum_required(VERSION 3.0)
project(cppcrc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-pthread")

include_directories(src/include)

add_definitions(-DCPPCRC_THREADSAFE) 

add_library(cppcrc 
    src/code_crc8.cc
    src/code_crc16.cc
    src/code_crc32.cc
    src/code_crc64.cc
    src/code_crcsick.cc
    src/code_crckrmit.cc
)

add_executable(testcrc tests/testcrc.cc)
target_link_libraries(testcrc cppcrc)

