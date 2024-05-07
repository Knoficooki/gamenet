cmake_minimum_required(VERSION 3.1)
project(client)

set(CLIENT_EXEC_NAME "gnc" CACHE STRING "The name of the executable.")

set(CLIENT_SOURCE_FOLDER "src" CACHE STRING "Path to source.")

file(GLOB_RECURSE CC_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "${CLIENT_SOURCE_FOLDER}/*.c")
file(GLOB_RECURSE CC_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${CLIENT_SOURCE_FOLDER}/*.h")

file(GLOB_RECURSE CCPP_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "${CLIENT_SOURCE_FOLDER}/*.cpp")
file(GLOB_RECURSE CCPP_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${CLIENT_SOURCE_FOLDER}/*.hpp")

file(GLOB_RECURSE CCXX_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "${CLIENT_SOURCE_FOLDER}/*.cxx")
file(GLOB_RECURSE CCXX_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${CLIENT_SOURCE_FOLDER}/*.hxx")


set(CCHEADERS ${CC_HEADERS} ${CCPP_HEADERS} ${CCXX_HEADERS})
set(CCSOURCES ${CC_SOURCES} ${CCPP_SOURCES} ${CCXX_SOURCES})


add_executable(client_app
	${CCSOURCES} 
	${CCHEADERS}
)

if(WIN32)
  target_link_libraries(client_app wsock32 ws2_32)
endif()


target_compile_definitions(client_app PRIVATE
                                $<$<CONFIG:Debug>:_DEBUG>
                            )

# Organisieren Sie die Dateien in einer Quellgruppe
source_group(TREE "${PROJECT_SOURCE_DIR}/${CLIENT_SOURCE_FOLDER}/" PREFIX "Source Files" FILES ${CCSOURCES})
source_group(TREE "${PROJECT_SOURCE_DIR}/${CLIENT_SOURCE_FOLDER}/" PREFIX "Header Files" FILES ${CCHEADERS})

set_target_properties(client_app PROPERTIES OUTPUT_NAME "${CLIENT_EXEC_NAME}")
set_target_properties(client_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
