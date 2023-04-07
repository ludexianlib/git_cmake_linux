cmake_minimum_required(VERSION 3.20)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

# 分开编译server client
set(PROJECT_NAME server)
project(${PROJECT_NAME})
set(SRC_LIST common_linux.cpp
             common_linux.h
             server_linux.cpp
             server_linux.h
)
add_executable(${PROJECT_NAME} ${SRC_LIST})

elseif(WIN32)

##### windows分开编译client和server
set(PROJECT_NAME server)
project(${PROJECT_NAME})
set(SRC_LIST server_win.cpp)
add_definitions(-D UNICODE)
add_executable(${PROJECT_NAME} ${SRC_LIST})

endif()