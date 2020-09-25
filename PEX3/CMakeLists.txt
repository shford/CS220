# cmake_minimum_required(VERSION <specify CMake version here>)
project(LinkedLists C)

set(CMAKE_C_STANDARD 99)

#add_library(LinkedLists library.c PEX3.c Queue.c Stack.c test_cases.c)
add_executable(PEX3 PEX3.c Stack.c Queue.c library.c postfix_math_lib.c)