cmake_minimum_required(VERSION 3.1)
project(server)

include_directories(${PROJECT_SOURCE_DIR}/include/)

set(SERVER_EXEC_NAME "sgn" CACHE STRING "The name of the executable.")

set(SOURCE_FOLDER_SERVER "src" CACHE STRING "Path to source.")

file(GLOB_RECURSE SC_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER_SERVER}/*.c")
file(GLOB_RECURSE SC_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER_SERVER}/*.h")

file(GLOB_RECURSE SCPP_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER_SERVER}/*.cpp")
file(GLOB_RECURSE SCPP_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER_SERVER}/*.hpp")

file(GLOB_RECURSE SCXX_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER_SERVER}/*.cxx")
file(GLOB_RECURSE SCXX_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${SOURCE_FOLDER_SERVER}/*.hxx")


set(SCHEADERS ${SC_HEADERS} ${SCPP_HEADERS} ${SCXX_HEADERS})
set(SCSOURCES ${SC_SOURCES} ${SCPP_SOURCES} ${SCXX_SOURCES})


add_executable(server_app
	$<TARGET_OBJECTS:sharedlibobj>
	${SCSOURCES} 
	${SCHEADERS}
)

if(WIN32)
  target_link_libraries(server_app wsock32 ws2_32)
endif()


target_compile_definitions(server_app PRIVATE
                                $<$<CONFIG:Debug>:_DEBUG>
                            )

set_target_properties(server_app PROPERTIES OUTPUT_NAME "${SERVER_EXEC_NAME}")
set_target_properties(server_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
