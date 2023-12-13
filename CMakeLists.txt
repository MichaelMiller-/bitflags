cmake_minimum_required(VERSION 3.18)
project(bitflags VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 26)

## header-only library
add_library(bitflags INTERFACE)

target_include_directories(bitflags INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_sources(bitflags INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/bitflags/bitflags.h)

include(CTest)
if (BUILD_TESTING) # option is created by CTest
    enable_testing()
    add_subdirectory(tests)
endif ()
