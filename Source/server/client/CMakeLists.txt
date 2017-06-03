cmake_minimum_required(VERSION 2.6)

#set(client ${PROJECT_NAME})


project(client)

aux_source_directory(.  SRC_LIST)

add_executable(client  ${SRC_LIST})

include_directories(./)
include_directories(/usr/local/include)
include_directories(/usr/local/lib)
include_directories(../common)

add_definitions(-g)


target_link_libraries(client -levent)
target_link_libraries(client libserver_common.a)
