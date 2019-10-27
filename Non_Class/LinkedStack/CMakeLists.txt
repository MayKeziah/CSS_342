cmake_minimum_required(VERSION 3.15)
project(LinkedStack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LinkedStack
        Stack.cpp
        Stack.h
        LinkedStackTest.cpp
        PrecondViolatedExcept.h
        PrecondViolatedExcept.cpp)
