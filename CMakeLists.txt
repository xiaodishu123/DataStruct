cmake_minimum_required(VERSION 4.0)
project(DataStruct C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

aux_source_directory(src SRC_FILES)
aux_source_directory(algorithms/for_list LIST_FILES)

add_executable(DataStruct main.c
        ${SRC_FILES}
        ${ALGORITHM_FILES}
        ${LIST_FILES}
        test.c
)

target_include_directories(DataStruct PRIVATE include)
