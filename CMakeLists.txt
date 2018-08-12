cmake_minimum_required(VERSION 3.0)

# Stuff about C and compiling
set(CMAKE_C_COMPILER /usr/local/bin/gcc-7)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g")

project("rya" C)

# The version number.
set(RYA_VERSION "v0.1.0")

include(CheckIncludeFile)
include(CheckSymbolExists)

check_include_file("sys/stat.h" HAVE_SYS_STAT_H)
if (NOT HAVE_SYS_STAT_H)
    message(FATAL_ERROR "sys/stat.h not found")
endif ()

check_include_file("stdint.h" HAVE_STDINT_H)

# This stuff is needed in rya_format
check_include_file("stdarg.h" HAVE_STD_ARG_H)
if (NOT HAVE_STD_ARG_H)
    message(FATAL_ERROR "stdarg.h not found")
endif ()

# We will define a shallow copy if it isn't there.
check_symbol_exists(va_copy stdarg.h HAVE_VA_COPY)

# Check for I/O related functions
check_symbol_exists(vsnprintf stdio.h HAVE_VSNPRINTF)

# Check for string related functions
check_symbol_exists(strnlen string.h HAVE_STRNLEN)

set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.c)
file(GLOB HEADERS ${HEADER_DIR}/*.h)

#file(GLOB VENDOR_INCLUDES ${PROJECT_SOURCE_DIR}/vendor/*)
#file(GLOB VENDOR_SOURCES ${PROJECT_SOURCE_DIR}/vendor/*/*.c)

#include_directories(${VENDOR_INCLUDES})

#add_executable(main ${SOURCES})
#target_link_libraries(main PRIVATE -lm -lz)

include_directories(${HEADER_DIR})

add_library(rya SHARED ${SOURCES} ${HEADERS})
target_compile_features(rya PUBLIC c_std_11)


configure_file("${HEADER_DIR}/rya.cmake.h" "${HEADER_DIR}/rya.h")
