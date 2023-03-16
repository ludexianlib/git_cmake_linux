cmake_minimum_required(VERSION 3.10)

project(main)

add_subdirectory("./include")

# 添加头文件
include_directories(.)

add_executable(main main.cpp)

target_link_libraries(main Add)
