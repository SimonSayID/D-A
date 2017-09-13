cmake_minimum_required(VERSION 3.8)
project(D-A)

set(CMAKE_C_STANDARD 11)

include_directories(
        "${PROJECT_SOURCE_DIR}/avl_tree/"
        "${PROJECT_SOURCE_DIR}/stack/"
        "${PROJECT_SOURCE_DIR}/rb_tree/"
        "${PROJECT_SOURCE_DIR}/sort/"
        "${PROJECT_SOURCE_DIR}/list/"
        "${PROJECT_SOURCE_DIR}/queue/"
        "${PROJECT_SOURCE_DIR}/hash/"
        "${PROJECT_SOURCE_DIR}/heap/"
)

file(
        GLOB SOURCE
        "avl_tree/*.h"
        "avl_tree/*.c"
        "stack/*.h"
        "stack/*.c"
        "rb_tree/*.h"
        "rb_tree/*.c"
        "sort/*.h"
        "sort/*.c"
        "list/*.h"
        "list/*.c"
        "queue/*.h"
        "queue/*.c"
        "hash/*.h"
        "hash/*.c"
        "heap/*.h"
        "heap/*.c"
        "*.h"
        "*.c"
)

add_executable(D-A ${SOURCE})