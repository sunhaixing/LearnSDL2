cmake_minimum_required(VERSION 3.14)

set(CMAKE_PROJECT_NAME Lesson04)

project(${CMAKE_PROJECT_NAME})

add_executable(${CMAKE_PROJECT_NAME} main.c)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2)