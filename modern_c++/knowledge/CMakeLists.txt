cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME main)
project(${PROJECT_NAME})

set(SRC_LIST DLLManager.hpp main.cpp)
set(CXX_STANDARD_REQUIRED 11)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# 添加预定义
add_definitions(-DWIN32 -DUNICODE)

# 依赖第三方库的路径
# link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

# 生成文件路径
# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Debug)
# set(CMAKE_INSTALL_RPATH ${PROJECT_SOURCE_DIR}/build/Debug)

# 设置可执行程序依赖当前目录库文件 linux
# set_target_properties(${PROJECT} PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_RPATH}")
# set_target_properties(${PROJECT} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
# set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")