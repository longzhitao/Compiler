cmake_minimum_required(VERSION 3.15)
project(C_Parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(C_Parser main.cpp scan.cpp scan.h globals.h semanteme.cpp semanteme.h)