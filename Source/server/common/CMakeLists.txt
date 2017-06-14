cmake_minimum_required(VERSION 2.6)


project(server_common)

aux_source_directory(.  SRC_LIST)

add_library(server_common  STATIC ${SRC_LIST})

include_directories(./)
include_directories(/usr/local/include)
include_directories(/usr/local/lib)

add_definitions(-g)
add_definitions(-std=c++11)
add_definitions(-lz)


install(FILES ./build/libserver_common.a DESTINATION /usr/local/lib)


target_link_libraries(server_common -levent)
target_link_libraries(server_common -lprotobuf)
target_link_libraries(server_common -pthread)
target_link_libraries(server_common -lpthread)
