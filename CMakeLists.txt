cmake_minimum_required(VERSION 3.0)

# Stuff about C and compiling
#set(CMAKE_C_COMPILER gcc)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g -O3")

project("rya" C)

# The version number.
set(RYA_VERSION_MAJOR 0)
set(RYA_VERSION_MINOR 2)
set(RYA_VERSION_PATCH 1)
set(RYA_VERSION_STRING "${RYA_VERSION_MAJOR}.${RYA_VERSION_MINOR}.${RYA_VERSION_PATCH}")


# Modules to include
include(CheckIncludeFile)
include(CheckSymbolExists)
include(GNUInstallDirs)

# Make sure standard things are there.
check_include_file("assert.h" HAVE_ASSERT_H)
if (NOT HAVE_ASSERT_H)
    message(FATAL_ERROR "assert.h not found")
endif ()
check_include_file("errno.h" HAVE_ERRNO_H)
if (NOT HAVE_ERRNO_H)
    message(FATAL_ERROR "errno.h not found")
endif ()
check_include_file("limits.h" HAVE_LIMITS_H)
if (NOT HAVE_LIMITS_H)
    message(FATAL_ERROR "limits.h not found")
endif ()
check_include_file("stdio.h" HAVE_STDIO_H)
if (NOT HAVE_STDIO_H)
    message(FATAL_ERROR "stdio.h not found")
endif ()
check_include_file("stdlib.h" HAVE_STDLIB_H)
if (NOT HAVE_STDLIB_H)
    message(FATAL_ERROR "stdlib.h not found")
endif ()
check_include_file("string.h" HAVE_STRING_H)
if (NOT HAVE_STRING_H)
    message(FATAL_ERROR "string.h not found")
endif ()


check_include_file("sys/stat.h" HAVE_SYS_STAT_H)
check_include_file("stdint.h" HAVE_STDINT_H)
check_include_file("stdarg.h" HAVE_STDARG_H)

# We will define a shallow copy if it isn't there.
check_symbol_exists(va_copy stdarg.h HAVE_VA_COPY)

# Check for I/O related functions
check_symbol_exists(vsnprintf stdio.h HAVE_VSNPRINTF)

# Check for string related functions
check_symbol_exists(strnlen string.h HAVE_STRNLEN)
check_symbol_exists(strndup string.h HAVE_STRNDUP)

#set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(CONFIG_DIR ${PROJECT_SOURCE_DIR}/cmake_config)

file(GLOB SOURCES ${SOURCE_DIR}/*.c)
file(GLOB HEADERS ${HEADER_DIR}/*.h)

#file(GLOB VENDOR_INCLUDES ${PROJECT_SOURCE_DIR}/vendor/*)
#file(GLOB VENDOR_SOURCES ${PROJECT_SOURCE_DIR}/vendor/*/*.c)

#include_directories(${VENDOR_INCLUDES})

#add_executable(main ${SOURCES})
#target_link_libraries(main PRIVATE -lm -lz)

include_directories(${HEADER_DIR})

# Configure files
configure_file("${CONFIG_DIR}/rya.cmake.h" "${HEADER_DIR}/rya.h")
configure_file("${CONFIG_DIR}/README.cmake.md" "${PROJECT_SOURCE_DIR}/README.md")

# These are the and other things to install....

install(FILES ${HEADER_DIR}/rya.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# rya_format
add_library(rya_format SHARED ${SOURCE_DIR}/rya_format.c)
set_target_properties(rya_format PROPERTIES VERSION ${RYA_VERSION_STRING})
set_target_properties(rya_format PROPERTIES PUBLIC_HEADER ${HEADER_DIR}/rya_format.h)


#target_compile_features(rya_format PRIVATE c_std_11)
target_include_directories(rya_format PRIVATE ${HEADER_DIR})
target_include_directories(rya_format PRIVATE ${SOURCE_DIR})

install(TARGETS rya_format
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# rya_file
add_library(rya_file SHARED ${SOURCE_DIR}/rya_file.c)
set_target_properties(rya_file PROPERTIES VERSION ${RYA_VERSION_STRING})
set_target_properties(rya_file PROPERTIES PUBLIC_HEADER ${HEADER_DIR}/rya_file.h)

#target_compile_features(rya_file PRIVATE c_std_11)
target_include_directories(rya_file PRIVATE ${HEADER_DIR})
target_include_directories(rya_file PRIVATE ${SOURCE_DIR})

install(TARGETS rya_file
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# rya_seq
add_library(rya_seq SHARED ${SOURCE_DIR}/rya_seq.c)
set_target_properties(rya_seq PROPERTIES VERSION ${RYA_VERSION_STRING})
set_target_properties(rya_seq PROPERTIES PUBLIC_HEADER ${HEADER_DIR}/rya_seq.h)

#target_compile_features(rya_seq PRIVATE c_std_11)
target_include_directories(rya_seq PRIVATE ${HEADER_DIR})
target_include_directories(rya_seq PRIVATE ${SOURCE_DIR})

install(TARGETS rya_seq
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

