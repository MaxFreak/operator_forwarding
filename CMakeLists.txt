cmake_minimum_required(VERSION 3.3)
project(operator_forwarding)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(operator_forwarding ${SOURCE_FILES})