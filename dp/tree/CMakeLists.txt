cmake_minimum_required(VERSION 3.10)

project(binarytree)

set(SRC_LIST BinaryTree.cpp
             main.cpp
             SqStack.cpp
             LinkQueue.cpp
)

add_executable(binarytree ${SRC_LIST})