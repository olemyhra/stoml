#This file is used to compile the Simple TOML library


cmake_minimum_required(VERSION 3.30)


project(STOML VERSION 2.0.0)
add_library(stoml SHARED stoml.c)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

#Options
option(BUILD_TEST "Build test executable" OFF)

set(GCC_OPTIONS
	-D_FORTIFY_SOURCE=2
	-fpie -Wl,-pie
	-Wall
	-Werror
	-O2
	-g3
	-fpic -shared
	-std=c17
	-pedantic
	-shared
)

set(CLANG_OPTIONS
	${GCC_OPTIONS}
)

set(MSVC_OPTIONS
	/guard:fl
	/analyze
	/sdl
	/permissive-
	/O2
	/W4
	/WX	
)


if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
	set(STOML_COMP_OPTIONS ${MSVC_OPTIONS})
	message(NOTICE "MSVC compiler detected")
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(STOML_COMP_OPTIONS ${CLANG_OPTIONS})
	message(NOTICE "Clang compiler detected")
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
	set(STOML_COMP_OPTIONS ${GCC_OPTIONS})
	message(NOTICE "GCC compiler detected")
endif()



set_target_properties(stoml PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_compile_options(stoml PRIVATE ${STOML_COMP_OPTIONS})

if(BUILD_TEST)
	add_subdirectory(test)
endif()


