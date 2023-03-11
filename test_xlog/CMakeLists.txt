cmake_minimum_required(VERSION 3.10)

project(test_xlog)

set(SRC_LIST test_xlog.cpp)


# 添加头文件
include_directories("../xlog")

# 添加静态库路径
link_directories("../xlog/build")

add_executable(test_xlog ${SRC_LIST})

# 添加链接静态库（项目名称，静态库名称）
target_link_libraries(test_xlog xlog)
