cmake_minimum_required(VERSION 3.13)
project(projects)

set(CMAKE_CXX_STANDARD 98)

include_directories(./include)

add_library(projects SHARED ./src/ilrd_details ./src/reactor/reactor.cpp
        ./src/storage/heap_storage.cpp ./src/scheduler/scheduler.cpp
        ./src/communicator/communicator.cpp ./src/logger/logger.cpp
        ./src/minion/minion.cpp ./src/reactor/demultiplexer.cpp
        ./src/protocol/vdr_protocol.cpp ./src/timer/timer.cpp
        ./src/udp_socket/udp_socket.cpp ./src/waitable_queue/proj_utils.cpp
        ./src/command/command.cpp ./src/thread_pool/thread_pool.cpp
        ./src/master/master.cpp
        ./src/nbd/nbd_communicator.cpp)

set_property(TARGET projects PROPERTY POSITION_INDEPENDENT_CODE ON)
include(GNUInstallDirs)

add_executable(logger ./src/logger/logger_test.cpp)
add_executable(minion ./src/minion/minion_test.cpp)
add_executable(reactor ./src/reactor/reactor_test.cpp
               ../system_programming/ping_pong_server/utils.cpp)
add_executable(scheduler ./src/scheduler/scheduler_test.cpp)
add_executable(scope_lock ./src/scope_lock/scope_lock_test.cpp)
add_executable(singleton ./src/singleton/singleton_test.cpp)
add_executable(timer ./src/timer/timer_test.cpp)
add_executable(udp_socket ./src/udp_socket/udp_socket_test.cpp)
add_executable(factory src/factory/factory.cpp)
add_executable(waitable_queue ./src/waitable_queue/waitable_queue_test.cpp)
add_executable(serializer ./src/serializer/serializer_test.cpp)
add_executable(thread_pool ./src/thread_pool/thread_pool_test.cpp)
#add_executable(dispatcher src/dispatcher/dispatcher_test.cpp)
add_executable(master src/master/master_test.cpp)

target_link_libraries(projects boost_system boost_thread boost_chrono pthread)

target_link_libraries(logger projects)
target_link_libraries(minion projects)
target_link_libraries(reactor projects)
target_link_libraries(scheduler projects)
target_link_libraries(scope_lock projects)
target_link_libraries(singleton projects)
target_link_libraries(timer projects)
target_link_libraries(udp_socket projects)
target_link_libraries(factory projects)
target_link_libraries(waitable_queue projects)
target_link_libraries(serializer projects)
target_link_libraries(master projects)
target_link_libraries(thread_pool projects boost_thread pthread)


