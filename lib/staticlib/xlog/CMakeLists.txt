cmake_minimum_required(VERSION 3.10)

project(xlog)

set(SRC_LIST xlog.cpp)
set(HEAD_LIST xlog.h)

add_library(xlog STATIC ${SRC_LIST} ${HEAD_LIST})
