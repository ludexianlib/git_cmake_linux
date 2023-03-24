cmake_minimum_required(VERSION 3.20)

# 只适用于windows
set(PROJECT_NAME server)
project(${PROJECT_NAME})

set(SRC_LIST server_win.cpp)
add_definitions(-D UNICODE)
add_executable(${PROJECT_NAME} ${SRC_LIST})