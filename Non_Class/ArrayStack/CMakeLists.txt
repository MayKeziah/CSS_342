cmake_minimum_required(VERSION 3.15)
project(ArrayStack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ArrayStack
    Stack.cpp
    Stack.h)
