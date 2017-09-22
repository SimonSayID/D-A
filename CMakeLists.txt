cmake_minimum_required(VERSION 3.8)
project(D-A)

set(CMAKE_C_STANDARD 11)

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