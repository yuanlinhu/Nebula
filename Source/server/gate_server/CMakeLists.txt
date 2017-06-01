cmake_minimum_required(VERSION 2.6)


project(gate)

add_definitions(-g)

aux_source_directory(.  SRC_LIST)

add_executable(gate  ${SRC_LIST})


include_directories(/usr/local/include)
include_directories(/usr/local/lib)
include_directories(./)
include_directories(../common)


link_directories("../common")
link_directories("../common/build")

find_library(COMM_LIB comm ../common NO_DEFAULT_PATH)



target_link_libraries(gate -levent)
target_link_libraries(gate libserver_common.a)