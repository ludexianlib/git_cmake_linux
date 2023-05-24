cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Observer)

set(SRC_LIST Observer.cpp)
set(CXX_STANDARD_REQUIRED 11)

add_executable(${PROJECT_NAME} ${SRC_LIST})