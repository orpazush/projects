cmake_minimum_required(VERSION 3.13)
project(bitarray)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(bitarray_test bitarray.cpp bitarray_test.cpp)
