cmake_minimum_required(VERSION 3.17)
project(shared_ptr)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


add_executable(shared_ptr_test shared_ptr_test.cpp)
