cmake_minimum_required(VERSION 3.13)
project(storage)

set(CMAKE_CXX_STANDARD 98)

include_directories(../../include)

add_executable(heap_storage heap_storage.cpp)
