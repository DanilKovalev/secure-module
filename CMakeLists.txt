cmake_minimum_required(VERSION 2.8)

project(secure_module)

if (NOT UNIX)
    message(FATAL_ERROR "Not Unix!")
endif()

set("${PROJECT}_VERSION_MAJ" 0)
set("${PROJECT}_VERSION_MIN" 1)
set("${PROJECT}_VERSION_PATCH" 0)
set("${PROJECT}_VERSION" ${${PROJECT}_VERSION_MAJ}.${${PROJECT}_VERSION_MIN}.${${PROJECT}_VERSION_PATCH})

set(GLOBAL_OUTPUT_PATH ${CMAKE_BINARY_DIR}/out)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${GLOBAL_OUTPUT_PATH}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${GLOBAL_OUTPUT_PATH}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${GLOBAL_OUTPUT_PATH}/lib)

message("Starting cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE OFF)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

enable_testing()
add_subdirectory(examples)
add_subdirectory(src)
