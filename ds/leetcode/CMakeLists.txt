cmake_minimum_required(VERSION 3.10)

project(leetcodeSolution)

include_directories(./array)
include_directories(./project)
aux_source_directory(./array ARRAY_SRC)
aux_source_directory(./project PROJECT_SRC)
aux_source_directory(./sort SORT_SRC)
aux_source_directory(. MAIN_SRC)

add_executable(leetcodeSolution  ${ARRAY_SRC} ${PROJECT_SRC} ${MAIN_SRC} ${SORT_SRC})
