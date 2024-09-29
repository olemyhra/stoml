#This file is used to compile the Simple TOML library


cmake_minimum_required(VERSION 3.30)


project(STOML VERSION 0.1.0)
add_library(stoml SHARED stoml.c)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

set_target_properties(stoml PROPERTIES VERSION 0.1.0 SOVERSION 0)
target_compile_options(stoml PRIVATE -Wall -Werror -O2 -g3 -fpic -shared -std=c99 -pedantic) 
