cmake_minimum_required(VERSION 3.20)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")

set(PROJECT_NAME shm)
project(${PROJECT_NAME})
set(SRC_LIST shmfifo_linux.cpp,
             put_linux.cpp
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