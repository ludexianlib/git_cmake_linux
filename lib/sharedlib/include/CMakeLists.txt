cmake_minimum_required(VERSION 3.10)

project(Add)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../) 

add_library(Add SHARED Add.cpp)
