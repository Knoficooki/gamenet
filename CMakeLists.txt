cmake_minimum_required(VERSION 3.1)
project(gamenet)

set(SOURCE_FOLDER "src" CACHE STRING "Path to source.")

set(BUILD_SERVER TRUE CACHE BOOL "Build the server app.")

set(BUILD_CLIENT TRUE CACHE BOOL "Build a client app.")

set(BOOST_LOCATION "C:\\Program Files\\boost\\boost_1_85_0\\" CACHE STRING "The Path to boost.")

include_directories(${BOOST_LOCATION})

include_directories(${SOURCE_FOLDER}/shared/)

file(GLOB_RECURSE SHARED_CPP_SOURCES ABSOLUTE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER}/shared/*.cpp")

file(GLOB_RECURSE SHARED_CPP_HEADER ABSOLUTE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER}/shared/*.hpp")

file(GLOB_RECURSE SHARED_C_SOURCES ABSOLUTE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER}/shared/*.c")

file(GLOB_RECURSE SHARED_C_HEADER ABSOLUTE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER}/shared/*.h")



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

set(SHARED_SOURCES ${SHARED_CPP_SOURCES} ${SHARED_C_SOURCES})
set(SHARED_HEADERS ${SHARED_CPP_HEADER} ${SHARED_C_HEADER})

message(STATUS ${SHARED_SOURCES})

add_library(sharedlibobj OBJECT ${SHARED_SOURCES} ${SHARED_HEADERS})

# shared libraries need PIC
set_property(TARGET sharedlibobj PROPERTY POSITION_INDEPENDENT_CODE 1)

if(${BUILD_SERVER})
	add_subdirectory("${SOURCE_FOLDER}/server/")
endif()

if(${BUILD_CLIENT})
	add_subdirectory("${SOURCE_FOLDER}/client/")
endif()
