cmake_minimum_required(VERSION 3.3)
project(os_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyThreadsLib.cpp MyThreadsLib.h)
add_executable(os_4 ${SOURCE_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(os_4 Threads::Threads)