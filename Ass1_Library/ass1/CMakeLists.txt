cmake_minimum_required(VERSION 3.15)
project(ass1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ass1
        library.cpp
        library.h
        main.cpp)
