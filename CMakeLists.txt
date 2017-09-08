cmake_minimum_required(VERSION 3.8)
project(D-A)

set(CMAKE_C_STANDARD 11)

include_directories(
        "${PROJECT_SOURCE_DIR}/avl_tree/"
        "${PROJECT_SOURCE_DIR}/stack/"
        "${PROJECT_SOURCE_DIR}/rb_tree/"
        "${PROJECT_SOURCE_DIR}/sort/"
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
        "*.h"
        "*.c"
)

add_executable(D-A ${SOURCE} rb_tree/rb_tree.c rb_tree/rb_tree.h)