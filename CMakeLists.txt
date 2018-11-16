cmake_minimum_required (VERSION 3.1)
project(mepcore VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "mepcore is library for multi expression programming")

set(MEPCORE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/mepcore")
set(MEPCORE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${MEPCORE_INCLUDE_DIR})

set(MEPCORE_SOURCES "")

link_directories(${CMAKE_CURRENT_BINARY_DIR})

include(src/CMakeLists.txt)
add_subdirectory(test)

add_library(mepcore SHARED ${MEPCORE_SOURCES})