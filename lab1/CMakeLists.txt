cmake_minimum_required(VERSION 3.27)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1 main.c)

add_executable(first_child first_child.c)
add_executable(second_child second_child.c)