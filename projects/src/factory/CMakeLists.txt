cmake_minimum_required(VERSION 3.13)
project(factory)

set(CMAKE_CXX_STANDARD 98)

include_directories(. ../../include)

add_executable(factory factory.cpp)
target_link_libraries(factory boost_system boost_thread)