cmake_minimum_required (VERSION 2.6)
project (MEPCore)

set(MEPCORE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/mepcore")
set(MEPCORE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("${MEPCORE_INCLUDE_DIR}")

add_subdirectory(src)