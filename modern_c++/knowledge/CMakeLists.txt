cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME main)
project(${PROJECT_NAME})

set(SRC_LIST main.cpp)
set(CXX_STANDARD_REQUIRED 11)

add_executable(${PROJECT_NAME} ${SRC_LIST})