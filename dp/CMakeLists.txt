cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Template)

set(SRC_LIST Template.cpp)
set(CXX_STANDARD_REQUIRED 11)

add_executable(${PROJECT_NAME} ${SRC_LIST})