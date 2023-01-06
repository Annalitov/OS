cmake_minimum_required(VERSION 3.15)
project(kursach)

set(CMAKE_CXX_STANDARD 14)


add_executable(os_kp
        main.cpp
        N2Allocator.cpp
        N2Allocator.h
        RMAllocator.cpp
        RMAllocator.h)