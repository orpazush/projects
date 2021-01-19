cmake_minimum_required(VERSION 3.13)
project(udp_socket)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(../../include)

add_executable(udp_socket_test udp_socket.cpp udp_socket_test.cpp)
