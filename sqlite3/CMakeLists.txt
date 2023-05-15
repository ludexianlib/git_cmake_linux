cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME sqlite)
project(${PROJECT_NAME})

set(SRC_LIST main.cpp)
set(CXX_STANDARD_REQUIRED 11)

# 添加头文件
include_directories(include/sqlite3.h)

# 生成静态库
add_library(sqlite3 STATIC include/shell.c include/sqlite3.c)

# 链接静态库路径
link_directories(build)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} sqlite3)