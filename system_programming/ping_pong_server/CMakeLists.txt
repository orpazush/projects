cmake_minimum_required(VERSION 3.17)
project(ping_pong_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(utils SHARED utils.cpp)

add_executable(server server.cpp)
add_executable(tcp_client tcp_client.cpp)
add_executable(udp_client udp_client.cpp)
add_executable(broadcast_client broadcast_client.cpp)

target_link_libraries(server pthread utils)
target_link_libraries(tcp_client utils)
target_link_libraries(udp_client utils)
target_link_libraries(broadcast_client utils)
