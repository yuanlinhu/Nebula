cmake_minimum_required(VERSION 2.6)


project(server_common)

aux_source_directory(.  SRC_LIST)

add_library(server_common  ${SRC_LIST})

include_directories(./)
include_directories(/usr/local/include)
include_directories(/usr/local/lib)

add_definitions(-g)


target_link_libraries(server_common -levent)
