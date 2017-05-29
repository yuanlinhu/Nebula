cmake_minimum_required(VERSION 2.6)


project(game)

aux_source_directory(.  SRC_LIST)

add_executable(game  ${SRC_LIST})

include_directories(./)
include_directories(/usr/local/include)
include_directories(/usr/local/lib)


target_link_libraries(game -levent)
