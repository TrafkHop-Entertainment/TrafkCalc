cmake_minimum_required(VERSION 3.10)
project(TrafkCalc C)

set(CMAKE_C_STANDARD 11)

add_executable(TrafkCalc main.c)
target_link_libraries(TrafkCalc m)
