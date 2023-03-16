cmake_minimum_required(VERSION 3.10)

project(main)

set(SRC_LIST main.cpp
             MGraph.cpp
)

add_executable(main ${SRC_LIST})