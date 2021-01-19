cmake_minimum_required(VERSION 3.17)
project(scheduler)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(../../include)

add_executable(scheduler_test ../reactor/reactor.cpp ../reactor/demultiplexer.cpp
                ../timer/timer.cpp scheduler.cpp ../logger/logger.cpp scheduler_test.cpp)

target_link_libraries(scheduler_test boost_system boost_chrono boost_thread)
