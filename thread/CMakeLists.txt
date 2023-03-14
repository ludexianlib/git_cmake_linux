cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME thread)
project(${PROJECT_NAME})

set(SRC_LIST main.cpp)

##### Linux平台设置编译选项
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

##### Windows平台设置编译选项
elseif(WIN32)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
# set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 附加manifest清单文件
# target_sources(${PROJECT_NAME} PRIVATE "${PROJECT_NAME}.manifest")
endif()

add_executable(${PROJECT_NAME} ${SRC_LIST})