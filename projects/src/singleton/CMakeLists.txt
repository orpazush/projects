cmake_minimum_required(VERSION 3.13)
project(singleton)

set(CMAKE_CXX_STANDARD 98)

include_directories(../../include)

add_executable(singleton_test singleton_test.cpp)

target_link_libraries(singleton_test boost_system boost_thread)