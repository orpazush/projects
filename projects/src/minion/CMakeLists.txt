cmake_minimum_required(VERSION 3.13)
project(minion)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(../../include)

add_executable(minion_test minion.cpp ../reactor/reactor.cpp ../reactor/demultiplexer.cpp
        ../udp_socket/udp_socket.cpp ../protocol/vdr_protocol.cpp
        ../communicator/communicator.cpp ../../../system_programming/ping_pong_server/utils.cpp
        minion_test.cpp)
