cmake_minimum_required(VERSION 2.6)


project(gate)

aux_source_directory(.  SRC_LIST)

add_executable(gate  ${SRC_LIST})

include_directories(./)


target_link_libraries(gate -levent)
