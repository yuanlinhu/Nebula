cmake_minimum_required(VERSION 2.6)


project(gate)

add_definitions(-g)

aux_source_directory(.  SRC_LIST)

add_executable(gate  ${SRC_LIST})


include_directories(/usr/local/include)
include_directories(./)
include_directories(../common)

add_definitions(-g)
add_definitions(-lz)
add_definitions(-std=c++11)

set(COMMON_LINK_DIR /home/share/Nebula/Source/server/common/build)

link_directories(/usr/local/lib)
link_directories(/home/share/Nebula/Source/server/common/build)

#find_library(COMM_LIB comm ../common NO_DEFAULT_PATH)


target_link_libraries(gate -pthread)
target_link_libraries(gate -lprotobuf)
target_link_libraries(gate -levent)
target_link_libraries(gate -lpthread)
target_link_libraries(gate libserver_common.a)
