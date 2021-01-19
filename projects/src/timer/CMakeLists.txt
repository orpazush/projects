cmake_minimum_required(VERSION 3.17)
project(timer)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(../reactor)
include_directories(../../include)

add_executable(timer ../reactor/reactor.cpp ../reactor/demultiplexer.cpp timer.cpp)
add_executable(timer_test timer ../reactor/reactor.cpp
                ../reactor/demultiplexer.cpp timer_test.cpp)

target_link_libraries(timer boost_system boost_chrono)
target_link_libraries(timer_test boost_system boost_chrono)

