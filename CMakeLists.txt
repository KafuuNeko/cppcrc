cmake_minimum_required(VERSION 3.0)
project(cppcrc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-pthread")

add_definitions(-DCPPCRC_THREADSAFE) 

add_library(cppcrc 
    include/cppcrc.hh
    include/cppcrc/encoder.hh
    include/cppcrc/code_base.hh

    include/cppcrc/code_crc8.hh
    src/code_crc8.cc
    
    include/cppcrc/code_crc16.hh
    src/code_crc16.cc

    include/cppcrc/code_crc32.hh
    src/code_crc32.cc

    include/cppcrc/code_crc64.hh
    src/code_crc64.cc

    include/cppcrc/code_crcsick.hh
    src/code_crcsick.cc

    include/cppcrc/code_crckrmit.hh
    src/code_crckrmit.cc

    include/cppcrc/code_crcdnp.hh
    src/code_crcdnp.cc
)

target_include_directories(cppcrc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

enable_testing()

add_executable(testcrc tests/testcrc.cc)
target_link_libraries(testcrc cppcrc)

add_test(
    NAME testcrc
    COMMAND testcrc
)