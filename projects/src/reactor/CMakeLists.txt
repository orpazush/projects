cmake_minimum_required(VERSION 3.13)
project(reactor)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(../../../system_programming/ping_pong_server)
include_directories(../../include)

add_executable(demultiplexer demultiplexer.cpp ../logger/logger.cpp)
add_executable(clients ../../../system_programming/ping_pong_server/utils.cpp
        clients.cpp)
add_executable(reactor_test demultiplexer reactor
        ../../../system_programming/ping_pong_server/utils.cpp reactor_test.cpp
        ../logger/logger.cpp)

target_link_libraries(demultiplexer boost_system boost_thread)
target_link_libraries(reactor_test boost_system boost_thread)