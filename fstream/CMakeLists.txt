cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME fstream)
project(${PROJECT_NAME})

set(SRC_LIST FLog.cpp)
set(CXX_STANDARD_REQUIRED 11)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# cmake --build . --config Release
# cmake .. -DCMAKE_BUILD_TYPE=Release