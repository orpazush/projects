cmake_minimum_required(VERSION 3.13)
project(communicator)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(../../include)

add_executable(communicator communicator.cpp)
