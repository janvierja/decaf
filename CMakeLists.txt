cmake_minimum_required(VERSION 3.0)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(decaf CXX)

set(decaf_VERSION_MAJOR 0)
set(decaf_VERSION_MINOR 1)
set(decaf_VERSION_PATCH 0)
set(decaf_VERSION "${decaf_VERSION_MAJOR}.${decaf_VERSION_MINOR}.${decaf_VERSION_PATCH}")

# Create output directory if it doesn't exist
set(LIBRARY_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/target)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${LIBRARY_OUTPUT_DIR}/${CMAKE_BUILD_TYPE})

# Build in Release mode by default
if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# Use xenv environment variables
include_directories(BEFORE SYSTEM $ENV{SGSBASE}/usr/include)
include_directories(AFTER SYSTEM $ENV{SGSBASE}/usr/include/sys)
include_directories(AFTER $ENV{CCINCDIR})
link_directories($ENV{SGSBASE}/usr/lib64 $ENV{SGSBASE}/lib $ENV{SGSBASE}/tls/lib)

# Flags
set(CMAKE_CXX_FLAGS "-std=gnu++0x -Wall -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual -Wreorder")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(decaf_OUTPUT_NAME decafd)
else()
	set(decaf_OUTPUT_NAME decaf)
endif()

set(decaf_LIB_SRCS
	src/lang/Object.cpp)

add_definitions(-D_REENTRANT)

add_library(decaf SHARED ${decaf_LIB_SRCS})
target_include_directories(decaf PRIVATE ${PROJECT_SOURCE_DIR}/include $ENV{BOOST}/include)
set_target_properties(decaf PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(decaf PROPERTIES VERSION ${decaf_VERSION})
set_target_properties(decaf PROPERTIES OUTPUT_NAME ${decaf_OUTPUT_NAME})
set_target_properties(decaf PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR}/${CMAKE_BUILD_TYPE})
