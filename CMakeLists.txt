cmake_minimum_required(VERSION 3.9)
project(cppcrc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/include)

add_library(cppcrc 
    src/code_crc8.cc
    src/code_crc16.cc
    src/code_crc32.cc
    src/code_crc64.cc
    src/code_crcsick.cc
    src/code_crckrmit.cc
)

add_executable(crc8 tests/crc8.cc)
target_link_libraries(crc8 cppcrc)

