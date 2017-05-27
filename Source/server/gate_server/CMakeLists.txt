#cmake_minimum_required(VERSION 2.6)

project(gate)
add_executable(gate main.cpp)


target_link_libraries(gate -levent)
