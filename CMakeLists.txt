cmake_minimum_required(VERSION 3.8)
project(alg)

set(CMAKE_C_STANDARD 11)

file(
        GLOB SOURCE
        "*.h"
        "*.c"
)

add_executable(alg ${SOURCE} config.c)