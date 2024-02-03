cmake_minimum_required(VERSION 3.1)
project(gn)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include_directories(include/)
include_directories(lib/)
include_directories(shared/)

set(CMAKE_FUNC_DIR "${CMAKE_SOURCE_DIR}/cmake/")

list(APPEND CMAKE_MODULE_PATH "./cmake/")

add_subdirectory(client/)
add_subdirectory(server/)
