cmake_minimum_required(VERSION 3.14)

set(CMAKE_PROJECT_NAME mi)

project(${CMAKE_PROJECT_NAME})

add_executable(${CMAKE_PROJECT_NAME} main.c app.c app.h app_error.c app_error.h app_window.c app_window.h)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 SDL2_image)