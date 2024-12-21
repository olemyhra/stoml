#This file is used to compile the Simple TOML library


cmake_minimum_required(VERSION 3.30)


project(STOML VERSION 1.1.0)
add_executable(test test.c)
target_link_libraries(test PUBLIC criterion)
target_link_libraries(test PUBLIC stoml)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

target_compile_options(stoml PRIVATE -Wall -Werror -O2 -g3 -fpic -std=c17 -pedantic) 
