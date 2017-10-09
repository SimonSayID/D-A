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
        "tree/avl/*.h"
        "tree/avl/*.c"
        "tree/rb/*.h"
        "tree/rb/*.c"
        "tree/splay/*.h"
        "tree/splay/*.c"
        "heap/binomial/*.h"
        "heap/binomial/*.c"
        "hash/*.h"
        "hash/*.c"
        "graph/ud_uw/*.h"
        "graph/ud_uw/*.c"
        "graph/ud_w/*.h"
        "graph/ud_w/*.c"
        "sort/*.h"
        "sort/*.c"
        "*.h"
        "*.c"
)

add_executable(D-A ${SOURCE})