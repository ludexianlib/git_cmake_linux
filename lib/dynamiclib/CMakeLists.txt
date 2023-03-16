cmake_minimum_required(VERSION 3.23)

project(xlog)

# 添加头文件
include_directories("xlog")

# 生成动态库，cmake自动添加xlog_EXPORTS预处理
add_library(xlog SHARED xlog/xlog.cpp)

add_executable(test_xlog test_xlog/test_xlog.cpp)

target_link_libraries(test_xlog xlog)
