cmake_minimum_required(VERSION 3.14)

set(CMAKE_PROJECT_NAME Lesson10)

project(${CMAKE_PROJECT_NAME})

add_executable(${CMAKE_PROJECT_NAME} main.c texture.c texture.h)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 SDL2_image)