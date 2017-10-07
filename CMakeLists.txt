cmake_minimum_required(VERSION 3.8)
project(D-A)

set(CMAKE_C_STANDARD 11)

file(
        GLOB SOURCE
        "list/*.h"
        "list/*.c"
        "stack/*.h"
        "stack/*.c"
        "queue/*.h"
        "queue/*.c"
        "avl_tree/*.h"
        "avl_tree/*.c"
        "rb_tree/*.h"
        "rb_tree/*.c"
        "sp_tree/*.h"
        "sp_tree/*.c"
        "bm_heap/*.h"
        "bm_heap/*.c"
        "hash/*.h"
        "hash/*.c"
        "graph/*.h"
        "graph/*.c"
        "sort/*.h"
        "sort/*.c"
        "*.h"
        "*.c"
)

add_executable(D-A ${SOURCE})