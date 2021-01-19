cmake_minimum_required(VERSION 3.13)
project(logger)

set(CMAKE_CXX_STANDARD 98)

include_directories(. ../../include)

add_executable(logger logger.cpp logger_test.cpp)

#target_link_libraries(logger boost_system boost_thread)
target_link_libraries(logger ../../lib/lib.so/lib_so)
