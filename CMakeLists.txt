cmake_minimum_required(VERSION 3.8)
project(D-A)

set(CMAKE_C_STANDARD 11)

include_directories(
        "${PROJECT_SOURCE_DIR}/avl_tree/"
        "${PROJECT_SOURCE_DIR}/stack/"
)

file(
        GLOB SOURCE
        "${PROJECT_SOURCE_DIR}/avl_tree/*.h"
        "${PROJECT_SOURCE_DIR}/avl_tree/*.c"
        "${PROJECT_SOURCE_DIR}/stack/*.h"
        "${PROJECT_SOURCE_DIR}/stack/*.c"
        "*.h"
        "*.c"
)

add_executable(D-A ${SOURCE})