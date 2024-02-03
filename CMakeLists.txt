cmake_minimum_required(VERSION 3.27)
project(course1 C)

set(CMAKE_C_STANDARD 11)

add_executable(course1 main.c)



add_subdirectory(libs1)
target_link_libraries(course1 data_structures)
target_link_libraries(course1 algorithms)
